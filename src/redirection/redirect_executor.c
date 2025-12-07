#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "../../include/tokenizer.h"
#include "../../include/trim.h"
#include "../../include/redirection/redirect_executor.h"
#include "../../include/redirection/redirect_helper.h"
extern char *find_redirection_operator(char *input_line);
extern int get_redirection_type(char *c);

/*
 * Executes command with stdout or stderr redirected to fd.
 *
 * Args:
 *   fd: file descriptor opened for output
 *   dest_fd: STDOUT_FILENO or STDERR_FILENO
 *   command: command string to execute
 */
static void exec_with_single_redirect(int fd, int dest_fd, char *command) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("[Shell ERROR]: fork failed");
        return;
    }

    if (pid == 0) {
        if (dup2(fd, dest_fd) == -1) {
            perror("[Shell ERROR]: dup2 failed");
            exit(1);
        }
        close(fd);

        char **args = tokenize_input(command);
        if (args == NULL || args[0] == NULL) {
            fprintf(stderr, "[Shell ERROR]: empty command\n");
            exit(1);
        }
        
        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    } else {
        waitpid(pid, NULL, 0);
    }
}

/*
 * Executes command with both stdout and stderr redirected to fd.
 *
 * Args:
 *   fd: file descriptor opened for output
 *   command: command string to execute
 */
static void exec_with_combined_redirect(int fd, char *command) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("[Shell ERROR]: fork failed");
        return;
    }

    if (pid == 0) {
        /* child process */
        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("[Shell ERROR]: dup2 stdout failed");
            exit(1);
        }
        if (dup2(fd, STDERR_FILENO) == -1) {
            perror("[Shell ERROR]: dup2 stderr failed");
            exit(1);
        }
        close(fd);

        char **args = tokenize_input(command);
        if (args == NULL || args[0] == NULL) {
            fprintf(stderr, "[Shell ERROR]: empty command\n");
            exit(1);
        }
        
        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    } else {
        waitpid(pid, NULL, 0);
    }
}

/*
 * Parses and executes command with output redirection.
 *
 * Args:
 *   redirect_type: type flag from redirected_or_appended()
 *   input_line: full command line with redirection
 */
void parse_redirect_or_append(int redirect_type, char *input_line) {
    if (input_line == NULL || redirect_type == 0) return;

    extern char *find_redirection_operator(char *input_line);
    char *gt_pos = find_redirection_operator(input_line);
    if (!gt_pos) {
        fprintf(stderr, "[Shell ERROR]: redirection operator not found\n");
        return;
    }

    /* determine append mode and skip amount */
    int append = (redirect_type == 2 || redirect_type == 4 || redirect_type == 6) ? 1 : 0;
    int skip_chars = append ? 2 : 1;  /* skip '>>' or '>' */

    /* for types with prefix (2>, 2>>, &>, &>>), exclude prefix from command */
    char *cmd_end = gt_pos;
    if (redirect_type >= 3) cmd_end--;  /* skip '2' or '&' */

    /* extract command part */
    size_t cmd_len = (size_t)(cmd_end - input_line);
    char *cmd_buf = strndup(input_line, cmd_len);
    if (!cmd_buf) {
        perror("strndup");
        return;
    }

    char *trimmed_cmd = trim(cmd_buf);
    if (trimmed_cmd == NULL || *trimmed_cmd == '\0') {
        fprintf(stderr, "[Shell ERROR]: empty command\n");
        free(cmd_buf);
        return;
    }

    /* extract file part */
    char *file_part = gt_pos + skip_chars;
    char *trimmed_file = trim(file_part);
    if (trimmed_file == NULL || *trimmed_file == '\0') {
        fprintf(stderr, "[Shell ERROR]: no file path specified\n");
        free(cmd_buf);
        return;
    }

    char *file_path = strdup(trimmed_file);
    if (!file_path) {
        perror("strdup");
        free(cmd_buf);
        return;
    }

    /* open file with appropriate flags */
    int flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
    int fd = open(file_path, flags, 0664);
    if (fd == -1) {
        perror("[Shell ERROR]: open");
        free(cmd_buf);
        free(file_path);
        return;
    }

    /* execute with appropriate redirection */
    if (redirect_type == 5 || redirect_type == 6) {
        /* &> or &>> : redirect both stdout and stderr */
        exec_with_combined_redirect(fd, trimmed_cmd);
    } else if (redirect_type == 3 || redirect_type == 4) {
        /* 2> or 2>> : redirect stderr only */
        exec_with_single_redirect(fd, STDERR_FILENO, trimmed_cmd);
    } else {
        /* 1 or 2 : redirect stdout only */
        exec_with_single_redirect(fd, STDOUT_FILENO, trimmed_cmd);
    }

    close(fd);
    free(cmd_buf);
    free(file_path);
}
