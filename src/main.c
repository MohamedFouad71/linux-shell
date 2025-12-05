#include "../include/shell.h"

int main() {
    while (1) {
        // Prompt
        display_prompt();
    
        // Get input from user
        char* line = read_input();
        
        // Tokenize input
        char** args = tokenize_input(line);

        // handling empty input and built-in commands
        if (args[0] == NULL || is_builtins(args, line)) {
            free(line);
            free(args);
            continue;
        }
        // Execute external command
        execute_command(args, line);

        free(args);
        free(line);
    }

    return 0;
}
