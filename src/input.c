#include "../include/shell.h"

char* read_input() {
    char *line = readline("");

    // Add the command to readline history
    if(strlen(line)>0){
        add_history(line);
    }
    return line;
}