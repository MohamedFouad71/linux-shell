#include "../../include/shell.h"

int is_builtins(char** args, char* line,char* historyFilePath) {
    addCommandToHistory(args, historyFilePath);
    if (strcmp(args[0], "exit") == 0) {
        free(line);
        free_tokenized_args(args);
        exit(0);
    }

    if (strcmp(args[0], "cd") == 0) {
        cd(args);
        return 1;
    }

    if (strcmp(args[0], "about") == 0) {
        about();
        return 1;
    }

    if (strcmp(args[0], "help") == 0) {
        if (args[1] != NULL) {
           
            help_specific(args[1]);
        } else {
            
            help();
        }
        

    if (strcmp(args[0], "count") == 0) {
        count(args);
        return 1;
    }
    if(strcmp(args[0],"history") == 0){
        printHistory(historyFilePath);
        return 1;
    }

    return 0; // Not a built-in command
}
