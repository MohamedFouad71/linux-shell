#include "../../include/pipeline/pipe_executer.h"
#include "tokenizer.h"
#include "executor.h"
#include "builtins.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void execute_pipeline(char *input_line,char* historyFilePath) {
    // 1. Split the input by the pipe symbol "|"
    char **commands = tokenize_input(input_line, "|");
    if (!commands) return;

    int num_commands = 0;
    while (commands[num_commands] != NULL) num_commands++;

    int i = 0;
    int prev_fd = -1; // Holds the read end of the previous pipe
    int fd[2];

    for (i = 0; i < num_commands; i++) {
        // Create a pipe for all commands EXCEPT the last one
        if (i < num_commands - 1) {
            if (pipe(fd) == -1) {
                perror("[Shell Error]: Pipe failed");
                return;
            }
        }

        pid_t id = fork();
        if (id == -1) {
            perror("[Shell Error]: Fork failed");
            return;
        }

        if (id == 0) {
            
            // If there is a previous pipe, read from it
            if (prev_fd != -1) {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }

            if (i < num_commands - 1) {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }

            char **command_args = tokenize_input(commands[i], " ");
            
            if (command_args[0] == NULL) {
                free(command_args);
                exit(0);
            }

            // check and excute
            if (is_builtins(command_args, input_line,historyFilePath)) {
                free(command_args);
                free(input_line);
                _exit(0);
            }

            execute_command(command_args, input_line);
            free(command_args);
            free(input_line);
            _exit(1);

        } else {
            
            // A. Close the write-end of the current pipe 
            // (Parent doesn't write; if left open, child hangs)
            if (i < num_commands - 1) {
                close(fd[1]);
            }

            // B. Close the OLD read-end (We are done with it)
            if (prev_fd != -1) {
                close(prev_fd);
            }

            // C. Save the current read-end for the next iteration
            if (i < num_commands - 1) {
                prev_fd = fd[0];
            }
        }
    }

    for (int k = 0; k < num_commands; k++) {
        wait(NULL);
    }
    free(commands);
}
