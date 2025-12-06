#include "../include/shell.h"
#include <linux/limits.h>

int main() {
    char historyFilePath[PATH_MAX];
    getHistoryFileDir(historyFilePath, PATH_MAX);
    while (1) {
        display_prompt();
    
        char* input_line = read_input();
        
        char** command_args = tokenize_input(input_line);

        // Handling empty input and built-in commands
        if (command_args[0] == NULL 
            || is_builtins(command_args, input_line, historyFilePath)) {
            free(input_line);
            free(command_args);
            continue;
        }

        execute_command(command_args, input_line);

        free(input_line);
        free(command_args);
    }

    return 0;
}
