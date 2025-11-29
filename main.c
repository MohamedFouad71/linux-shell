#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    while (1) {

    // Prompt
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    
    char hostname[1024];
    gethostname(hostname, sizeof(hostname));

    char *username = getenv("USER");
    printf(">>%s@%s:%s$ ", username, hostname, cwd);

    // Get input from user
    char *line = NULL;
    size_t n = 0; 
    ssize_t numberOfChars; 

    // Replace '\n' (from getline output) with '\0' for proper execution
    numberOfChars = getline(&line, &n, stdin);
    line[numberOfChars - 1] = '\0';
    
    // Tokenize input
    char *args[20]; 
    int i = 0;
    char *command = strtok(line, " ");
    if (command == NULL) {
        free(line);
        continue;
    }
    // handling exit
    if (strcmp(command, "exit") == 0) {
        free(line);
        break;
    }
    // if (strcmp(command, "cd") == 0 {
    
    // })
    while (command != NULL) {
        args[i] = command;
        i++;
        command = strtok(NULL, " \n");
    }
    args[i] = NULL;

    // handling cd
    if (strcmp(args[0], "cd") == 0) {

        if(args[1] == NULL || args[1] == "~") {
            chdir(getenv("HOME"));
        }
        else {
            if (chdir(args[1]) == -1) {
                perror("[Error], Unable to change directory");
            }
        }
        free(line);
        continue;
    }

    // Excute command
    __pid_t pid = fork();

    // child process
    if (pid == -1) {
        perror("Fork Failed");
        exit(1);
    }

    if (pid == 0) {
        execvp(args[0], args);

        perror("execvp failed");
        exit(1);
    }
    wait(NULL);

    free(line);
    
    }

    return 0;
}