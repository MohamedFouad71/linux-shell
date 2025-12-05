#include "../include/shell.h"

char** tokenize_input(char* line) {
    char** args = malloc(20 * sizeof(char*)); // dynamic allocation
    int i = 0;
    char* command = strtok(line, " ");
    if (command == NULL) {
        args[0] = NULL;
        return args;
    }

    // Parse the rest of the arguments
    while (command != NULL) {
        args[i] = command;
        i++;
        command = strtok(NULL, " \n");
    }
    args[i] = NULL;

    return args;
}