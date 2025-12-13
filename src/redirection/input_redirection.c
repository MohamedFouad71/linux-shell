/* src/redirection/input_redirection.c */
#include "../../include/shell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// Helper: Find the '<' character outside of quotes
static char *find_input_operator(char *line) {
    int in_double = 0, in_single = 0;
    for (char *p = line; *p; ++p) {
        if (*p == '\\' && *(p + 1)) { p++; continue; }
        if (!in_single && *p == '"') { in_double = !in_double; continue; }
        if (!in_double && *p == '\'') { in_single = !in_single; continue; }
        
        if (!in_single && !in_double && *p == '<') return p;
    }
    return NULL;
}

// 1. Detection Function
int check_input_redirection(char *line) {
    if (!line) return 0;
    char *pos = find_input_operator(line);
    if (!pos) return 0;

    // Check if it is '<<'
    if (*(pos + 1) == '<') return 2; // Here Document
    return 1; // Standard Input Redirection
}

// Helper: Handle '<<' (Here Document)
// Reads from user until delimiter, saves to temp file, returns temp filename
static char *handle_heredoc_input(char *delimiter) {
    static char temp_file[] = ".temp_heredoc";
    FILE *fp = fopen(temp_file, "w");
    if (!fp) {
        perror("fopen heredoc");
        return NULL;
    }

    char *line = NULL;
    size_t len = 0;
    
    while (1) {
        printf("> "); // Secondary prompt (standard in shells)
        ssize_t read = getline(&line, &len, stdin);
        if (read == -1) break;

        // Remove newline for comparison
        if (line[read - 1] == '\n') line[read - 1] = '\0';

        if (strcmp(line, delimiter) == 0) break;

        fprintf(fp, "%s\n", line);
    }
    
    free(line);
    fclose(fp);
    return temp_file;
}

// 2. Execution Function
void execute_input_redirection(int type, char *line) {
    char *op_pos = find_input_operator(line);
    if (!op_pos) return;

    // 1. Split Command and File/Delimiter
    int skip = (type == 2) ? 2 : 1; // Skip '<' or '<<'
    
    // Extract Command (Left side)
    size_t cmd_len = op_pos - line;
    char *cmd_buf = strndup(line, cmd_len);
    char *command = trim(cmd_buf);

    // Extract File or Delimiter (Right side)
    char *target = trim(op_pos + skip);

    if (!command || !*command || !target || !*target) {
        fprintf(stderr, "[Shell Error]: Syntax error near unexpected token\n");
        free(cmd_buf);
        return;
    }

    // 2. Handle Here-Doc Logic (Create temp file if needed)
    char *input_file = target;
    if (type == 2) {
        input_file = handle_heredoc_input(target); // Writes user input to .temp_heredoc
        if (!input_file) {
            free(cmd_buf);
            return;
        }
    }

    // 3. Fork and Execute
    pid_t pid = fork();
    if (pid == 0) {
        // Child Process
        int fd = open(input_file, O_RDONLY);
        if (fd == -1) {
            perror("[Shell Error]: Cannot open input file");
            exit(1);
        }

        // Redirect File -> Stdin (0)
        dup2(fd, STDIN_FILENO);
        close(fd);

        // Execute Command
        char **args = tokenize_input(command, " ");
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    } else if (pid > 0) {
        // Parent Process
        wait(NULL);
        
        // Cleanup temp file if it was a Here-Doc
        if (type == 2) {
            unlink(input_file);
        }
    } else {
        perror("fork");
    }

    free(cmd_buf);
}
