#include "../include/shell.h"

int main() {
    while (1) {
        display_prompt();
    
        char* input_line = read_input();
        int redirected_or_appended = is_redirected_or_appended(input_line);
        int file_descriptor = -1; // used with redirection

        if (redirected_or_appended) {
            /* pass the flag (1 = '>', 2 = '>>') */
            parse_redirect_or_append(redirected_or_appended, input_line);
            continue;
        }
        
        char** command_args = tokenize_input(input_line);

        if (redirected_or_appended)
        {
            //#############################
        }
        

        // Handling empty input and built-in commands
        if (command_args[0] == NULL || is_builtins(command_args, input_line)) {
            free(input_line);
            free(command_args);
            continue;
        }

        execute_command(command_args, input_line);

        free(input_line);
        free(command_args);
        if (file_descriptor > 0) close(file_descriptor);
    }

    return 0;
}
