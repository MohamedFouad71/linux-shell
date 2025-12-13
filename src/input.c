#include "../include/shell.h"

char* read_input(char* prompt) {
    char *line = readline(prompt);

    // Add the command to readline history
    if(strlen(line)>0){
        add_history(line);
    }
    
    return line;
}