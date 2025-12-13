/* src/main.c */
#include "../include/shell.h"
#include <linux/limits.h>

int main() {
    char historyFilePath[PATH_MAX];
    getHistoryFileDir(historyFilePath, PATH_MAX);
    
    while (1) {
        char prompt [MAXIMUM_LINE_LENGTH];
        get_prompt(prompt);
    
        char* input_line = read_input(prompt);
        if (!input_line) break; // Handle Ctrl+D (EOF)

        // 1. Check Pipes
        if (has_pipe(input_line)) {
            execute_pipeline(input_line, historyFilePath);
            free(input_line);
            continue;
        }
        
        // 2. Check Input Redirection (< , <<)  <-- NEW CODE
        int in_type = check_input_redirection(input_line);
        if (in_type > 0) {
            execute_input_redirection(in_type, input_line);
            free(input_line);
            continue;
        }

        // 3. Check Output Redirection (>, >>)
        int redirection_type = redirected_or_appended(input_line);
        if (redirection_type) {
            parse_redirect_or_append(redirection_type, input_line);
            free(input_line); // Don't forget to free
            continue;
        }
        
        // 4. Normal Commands
        char** command_args = tokenize_input(input_line, " ");

        if (command_args[0] == NULL 
            || is_builtins(command_args, input_line, historyFilePath)) {
            free(input_line);
            free_tokenized_args(command_args);
            continue;
        }

        execute_command(command_args, input_line);

        free(input_line);
        free_tokenized_args(command_args);
    }

    return 0;
}
