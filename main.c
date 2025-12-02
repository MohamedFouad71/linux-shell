#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef unsigned long long u64;
#define MAXIMUM_LINE_LENGTH 1024


int main(int argc, char *argv[]) {

    while (1) {

    // Prompt
    char cwd    
    [1024];
    getcwd(cwd, sizeof(cwd));
    
    char hostname[1024];
    gethostname(hostname, sizeof(hostname));

    char *username = getenv("USER");
    printf(">%s@%s:%s$ ", username, hostname, cwd);

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

    while (command != NULL) {
        args[i] = command;
        i++;
        command = strtok(NULL, " \n");
    }
    args[i] = NULL;
    // FULL cd implementation: cd, cd ~, cd -, cd .., cd ., cd ~/folder
    static char prev_dir[1024] = "";  // store previous directory

    if (strcmp(args[0], "cd") == 0) {
        char *target = args[1];

        // cd  → go HOME
        if (target == NULL) {
            target = getenv("HOME");
        }
        // cd ~
        else if (strcmp(target, "~") == 0) {
            target = getenv("HOME");
        }
        // cd -
        else if (strcmp(target, "-") == 0) {
            if (prev_dir[0] == '\0') {
                printf("No previous directory\n");
                free(line);
                continue;
            }
            printf("%s\n", prev_dir); // like bash: print the old path
            target = prev_dir;
        }
        // cd ~/folder
        else if (target[0] == '~' && target[1] == '/') {
            static char temp[1024];
            snprintf(temp, sizeof(temp), "%s%s", getenv("HOME"), target + 1);
            target = temp;
        }

        // save current directory before changing
        char current[1024];
        getcwd(current, sizeof(current));

        if (chdir(target) != 0) {
            perror("cd");
        } else {
            strcpy(prev_dir, current);  // only update previous dir AFTER successful cd
        }

        free(line);
        continue;
    }

    // Handle count
    if(strcmp(args[0], "count") == 0){

        FILE* file = fopen(args[1], "r");
        if(file == NULL){
            // Error occured while openning file
            perror("Couldn't open file");
            free(line);
            continue;
        }

        u64 lineCounter = 0, wordCounter = 0, charCounter = 0;

        char fileLine[MAXIMUM_LINE_LENGTH];
        while(fgets(fileLine, MAXIMUM_LINE_LENGTH, file) != NULL){
            ++lineCounter;
            
            // count number of characters in line
            size_t lineLength = strlen(fileLine);
            if(fileLine[lineLength-1] == '\n') --lineLength;
            charCounter += lineLength;
            
            // Count number of words in line
            char* word = strtok(fileLine, " \n");
            while(word != NULL){
                ++wordCounter;
                word = strtok(NULL, " \n");
            }

        }
        if(fclose(file) == EOF) 
            perror("Couldn't close file");

        // Print counters
        printf("%llu %llu %llu %s\n", lineCounter, wordCounter, charCounter, args[1]);
        free(line);
        continue;
    }

    // Exec command
    pid_t pid = fork();

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
