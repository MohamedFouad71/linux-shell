#include "../include/shell.h"

char* read_input() {
    char *line = NULL;
    size_t n = 0; 
    ssize_t numberOfChars; 

    // Read input line from user
    numberOfChars = getline(&line, &n, stdin);
    if (numberOfChars == -1) {
        free(line);
        return NULL;
    }

    // Replace '\n' (from getline output) with '\0' for proper execution
    line[numberOfChars - 1] = '\0';
    return line;
}