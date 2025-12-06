#include "redirection_append.h"
#include "tokenizer.h"
#include "trim.h"

/*
 * Returns:
 *   0 - no output redirection
 *   1 - has '>'  (overwrite redirection)
 *   2 - has '>>' (append redirection)
 * Properly skips escaped characters (\> or \>>).
 */
int is_redirected_or_appended(char *line) {
    if (line == NULL) return 0;

    int in_double_quotes = 0;
    int in_single_quotes = 0;

    for (char *c = line; *c != '\0'; ++c) {
        /* handle escape sequence */
        if (*c == '\\' && *(c + 1) != '\0') {
            c += 2;
            continue;
        }

        if (!in_single_quotes && *c == '"') {
            in_double_quotes = !in_double_quotes;
            continue;
        }
        if (!in_double_quotes && *c == '\'') {
            in_single_quotes = !in_single_quotes;
            continue;
        }

        if (in_single_quotes || in_double_quotes) continue;

        if (*c == '>') {
            return (*(c + 1) == '>') ? 2 : 1;
        }
    }

    return 0;
}

static void exec_redirect_or_append(int src_file_descriptor, char *command_part) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("[Shell ERROR]: fork failed");
        return;
    }

    if (pid == 0) {
        /* child */
        if (dup2(src_file_descriptor, STDOUT_FILENO) == -1) {
            perror("[Shell ERROR]: dup2 failed");
            exit(1);
        }
        close(src_file_descriptor);

        /* command_part is a mutable string allocated by caller */
        char **command_with_args = tokenize_input(command_part);
        if (command_with_args == NULL || command_with_args[0] == NULL) {
            fprintf(stderr, "[Shell ERROR]: empty command for redirection\n");
            exit(1);
        }
        execvp(command_with_args[0], command_with_args);
        perror("execvp failed");
        /* if execvp fails, exit child */
        exit(1);
    } else {
        /* parent */
        waitpid(pid, NULL, 0);
    }
}

void parse_redirect_or_append(int redirect_or_append, char *input_line) {
    if (input_line == NULL) return;

    /* locate first '>' outside quotes and not escaped */
    char *p = input_line;
    char *gt = NULL;
    int in_double = 0, in_single = 0;
    while (*p) {
        if (*p == '\\' && *(p + 1) != '\0') { p += 2; continue; }
        if (!in_single && *p == '"') { in_double = !in_double; p++; continue; }
        if (!in_double && *p == '\'') { in_single = !in_single; p++; continue; }
        if (!in_single && !in_double && *p == '>') { gt = p; break; }
        p++;
    }

    if (!gt) {
        fprintf(stderr, "[Shell ERROR]: No '>' found\n");
        return;
    }

    int append = (redirect_or_append == 2) ? 1 : 0;

    /* split command and file parts */
    size_t cmd_len = (size_t)(gt - input_line);
    char *command_part = strndup(input_line, cmd_len);
    if (!command_part) {
        perror("strndup");
        return;
    }
    /* move file pointer past one or two '>' chars */
    char *file_part = gt + (append ? 2 : 1);

    /* trim whitespace around both parts */
    char *trimmed_cmd = trim(command_part);
    char *trimmed_file = trim(file_part);

    if (trimmed_file == NULL || *trimmed_file == '\0') {
        fprintf(stderr, "[Shell ERROR]: No path found after '>'\n");
        free(command_part);
        return;
    }

    char *file_path = strdup(trimmed_file);
    if (!file_path) {
        perror("strdup");
        free(command_part);
        return;
    }

    int flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
    int fd = open(file_path, flags, 0664);
    if (fd == -1) {
        perror("[Shell ERROR]: open failed");
        free(command_part);
        free(file_path);
        return;
    }

    /* execute the command with stdout redirected */
    exec_redirect_or_append(fd, trimmed_cmd);

    close(fd);
    free(command_part);
    free(file_path);
}
