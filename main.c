#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef unsigned long long u64;
#define MAXIMUM_LINE_LENGTH 1024


void about() {
    const char* blue   = "\033[1;34m";
    const char* green  = "\033[1;32m";
    const char* yellow = "\033[1;33m";
    const char* magenta= "\033[1;35m";
    const char* reset  = "\033[0m";

    printf("%s============================================%s\n", magenta, reset);
    printf("%s✨ Glitchy ✨%s\n", blue, reset);
    printf("%sIntoduced To:%s Eng. Omar Al-Hussiny.\n", green, reset);
    printf("%sDeveloped by:%s Kareem Hany, Muhammed Fouad, Muhammed Ashraf, Muhammed Fatooh, Yehya Hamdy, Ahmed Abdullatif and Somia Khaled.\n", green, reset);
    printf("%s--------------------------------------------%s\n", magenta, reset);
    printf("%s📄 Description:%s\n", yellow, reset);
    printf("Glitchy is a lightweight Linux-like terminal designed for learning\n");
    printf("and experimentation. It provides a fully functional command-line interface\n");
    printf("with support for external commands, built-in commands, and advanced\n");
    printf("features such as piping, I/O redirection, and command history.\n\n");
    printf("%s⚡ Key Features:%s\n", yellow, reset);
    printf("  • Built-in commands: cd, exit, help, history, about, clear, count\n");
    printf("  • Execute external Linux commands via fork() and execvp()\n");
    printf("  • Command piping (|) to chain multiple commands\n");
    printf("  • Input/output redirection using >, >>, and <\n");
    printf("  • Colored prompt showing username@hostname\n");
    printf("  • Persistent command history saved to file\n");
    printf("  • Error handling for invalid commands\n");
    printf("  • Multi-platform compatible (tested on Linux-based systems)\n");
    printf("  • Educational: Understand shell internals and system calls\n\n");
    printf("%s💡 Tips:%s\n", yellow, reset);
    printf("  • Use 'help' to see all available commands.\n");
    printf("  • Commands support standard Linux arguments and options.\n");
    printf("  • Use 'history' to quickly repeat previous commands.\n\n");
    printf("%s🚀 Enjoy exploring your Glitchy!%s\n", green, reset);
    printf("%s============================================%s\n", magenta, reset);
}


int main(int argc, char *argv[]) {

    while (1) {

    // Prompt
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    
    char hostname[1024];
    gethostname(hostname, sizeof(hostname));

    char *username = getenv("USER");
    printf(">%s@%s:%s$ ", username, hostname, cwd);

    // Get input from user
    char *line = NULL;
    size_t n = 0; 
    ssize_t numberOfChars; 

    // Read line safely
    numberOfChars = getline(&line, &n, stdin);

    // ===== FIX 1: Prevent segmentation fault from getline =====
    if (numberOfChars <= 0) {
        free(line);
        continue;
    }

    if (line[numberOfChars - 1] == '\n')
        line[numberOfChars - 1] = '\0';
    // ==========================================================

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

        // ===== FIX 2: Prevent writing outside args array =====
        if (i >= 19) {
            args[19] = NULL;
            break;
        }
        // =====================================================

        args[i] = command;
        i++;
        command = strtok(NULL, " \n");
    }
    args[i] = NULL;

    // FULL cd implementation
    static char prev_dir[1024] = "";  // store previous directory
    
    if (strcmp(args[0], "cd") == 0) {
        char *target = args[1];
        
        if (target == NULL) {
            target = getenv("HOME");
        }
        else if (strcmp(target, "~") == 0) {
            target = getenv("HOME");
        }
        else if (strcmp(target, "-") == 0) {
            if (prev_dir[0] == '\0') {
                printf("No previous directory\n");
                free(line);
                continue;
            }
            printf("%s\n", prev_dir);
            target = prev_dir;
        }
        else if (target[0] == '~' && target[1] == '/') {
            static char temp[1024];
            snprintf(temp, sizeof(temp), "%s%s", getenv("HOME"), target + 1);
            target = temp;
        }
        
        char current[1024];
        getcwd(current, sizeof(current));
        
        if (chdir(target) != 0) {
            perror("cd");
        } else {
            strcpy(prev_dir, current);
        }
        
        free(line);
        continue;
    }
    
    // handling about
    if (strcmp(args[0], "about") == 0) {
        about();
        free(line);
        continue;
    }
    
    // Handle count
    if(strcmp(args[0], "count") == 0){

        FILE* file = fopen(args[1], "r");
        if(file == NULL){
            perror("Couldn't open file");
            free(line);
            continue;
        }

        u64 lineCounter = 0, wordCounter = 0, charCounter = 0;

        char fileLine[MAXIMUM_LINE_LENGTH];
        while(fgets(fileLine, MAXIMUM_LINE_LENGTH, file) != NULL){
            ++lineCounter;
            
            size_t lineLength = strlen(fileLine);
            if(fileLine[lineLength-1] == '\n') --lineLength;
            charCounter += lineLength;
            
            char* word = strtok(fileLine, " \n");
            while(word != NULL){
                ++wordCounter;
                word = strtok(NULL, " \n");
            }

        }
        if(fclose(file) == EOF) 
            perror("Couldn't close file");

        printf("%llu %llu %llu %s\n", lineCounter, wordCounter, charCounter, args[1]);
        free(line);
        continue;
    }

    // Help
    if (strcmp(args[0], "help") == 0) {
        printf("\n--- My Simple Shell Help ---\n");
        
        printf("GNU bash, version 5.3.3(1)-release (x86_64-pc-linux-gnu)\n");
        printf("These shell commands are defined internally.  Type `help' to see this list.\n");
        printf("Type `help name' to find out more about the function `name'.\n");
        printf("Use `info bash' to find out more about the shell in general.\n");
        printf("Use `man -k' or `info' to find out more about commands not in this list.\n\n");
        printf("A star (*) next to a name means that the command is disabled.\n\n");

        printf("\n[1] Built-in Commands (Custom Implemented):\n");
        printf("  cd <path>        : Change directory. Supports (~ for home, - for prev, .. for up)\n");
        printf("  count <filename> : Analyze file (counts lines, words, and characters)\n");
        printf("  exit             : Terminate the shell session\n");
        printf("  help             : Display this help message\n");

        printf("\n[2] Common External Commands:\n");
        printf("  ls [-l] [-a]     : List directory contents\n");
        printf("  pwd              : Print current directory\n");
        printf("  mkdir <dirname>  : Create directory\n");
        printf("  rm <filename>    : Delete a file\n");
        printf("  rmdir <dirname>  : Remove empty directory\n");
        printf("  cp <src> <dest>  : Copy file\n");
        printf("  mv <src> <dest>  : Move or rename\n");
        printf("  cat <filename>   : Show file content\n");
        printf("  grep <txt> <file>: Search text\n");
        printf("  clear            : Clear screen\n");

        printf("\nNote: You can execute ANY Linux command installed.\n\n");

        free(line);
        continue;
    }

    // Exec command
    pid_t pid = fork();

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
