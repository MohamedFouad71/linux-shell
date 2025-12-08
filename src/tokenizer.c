// #include "../include/shell.h"
#include "tokenizer.h"
#include "trim.h"
// #include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** tokenize_input(char* line, char *delim) {
    char** args = malloc(20 * sizeof(char*)); // dynamic allocation
    int i = 0;
    char* command = strtok(line, delim);

    while  (command != NULL) {
        command = trim(command);
        args[i++] = command;
        command = strtok(NULL, delim);
    }
    args[i] = NULL;

    return args;
}