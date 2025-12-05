#include "../include/shell.h"

void execute_command(char** args, char* line) {
    pid_t pid = fork();

    // Handle the failure of fork
    if (pid == -1) {
        perror("Fork Failed");
        exit(1);
    }

    // Child process will run this block
    if (pid == 0) {
        execvp(args[0], args);

        perror("execvp failed");
        free(args);
        free(line);
        exit(1);
    }

    // Wait for child to terminate
    wait(NULL);
}