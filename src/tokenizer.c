#include "../include/shell.h"

/*
 * expand_variables
 * ----------------
 * Expands environment variables in the form $VAR inside src
 * and writes the expanded result into dest.
 *
 * Example:
 *   src  = "Hello $USER"
 *   dest = "Hello kareem"
 */
void expand_variables(const char* src, char* dest) {
    int i = 0;   // index for src
    int d = 0;   // index for dest
    int len = strlen(src);

    while (i < len) {
        // Detect variable expansion
        if (src[i] == '$') {
            i++; // skip '$'

            char varname[256];
            int v = 0;

            // Read variable name: letters, digits, underscore
            while (i < len && (isalnum(src[i]) || src[i] == '_')) {
                varname[v++] = src[i++];
            }
            varname[v] = '\0';

            // Get environment variable value
            const char* val = getenv(varname);
            if (val)
                d += sprintf(dest + d, "%s", val);
        } else {
            // Normal character, copy as-is
            dest[d++] = src[i++];
        }
    }
    // Null-terminate destination string
    dest[d] = '\0';
}

/*
 * tokenize_input
 * --------------
 * Splits the input line into tokens.
 *
 * - If delimiter is NOT space (" "), use simple strtok-based splitting
 *   (used for pipes, redirections, etc.).
 *
 * - If delimiter IS space (" "), use a smart tokenizer that supports:
 *   - Single quotes ('')
 *   - Double quotes ("")
 *   - Escaped quotes (\", \')
 *   - Environment variable expansion ($VAR)
 *
 * Returns:
 *   A NULL-terminated array of strings (char**).
 *   Each token is allocated on the heap and must be freed later.
 */
char** tokenize_input(char* line, char *delim) {
    // Simple tokenizer for non-space delimiters (e.g. "|")
    if (strcmp(delim, " ") != 0) {
        char** args = malloc(64 * sizeof(char*));
        int i = 0;
        char* token = strtok(line, delim);
        while (token != NULL) {
            args[i++] = strdup(token); // duplicate token to heap
            token = strtok(NULL, delim);
        }
        args[i] = NULL;
        return args;
    }

    // Smart tokenizer for space delimiter
    char** args = malloc(64 * sizeof(char*));
    int token_index = 0;
    int i = 0;
    int len = strlen(line);

    while (i < len) {
        // Skip leading spaces
        while (i < len && isspace(line[i])) i++;
        if (i >= len) break;

        char buffer[1024];
        int b = 0;
        int is_single_quote = 0;
        int is_double_quote = 0;

        // Detect opening quote
        if (line[i] == '\'') { is_single_quote = 1; i++; }
        else if (line[i] == '"') { is_double_quote = 1; i++; }

        // Read token characters
        while (i < len) {
            // End of quoted token
            if (is_single_quote && line[i] == '\'') { i++; break; }
            if (is_double_quote && line[i] == '"') { i++; break; }

            // Handle escaped quotes
            if (line[i] == '\\' && (line[i+1] == '"' || line[i+1] == '\'')) {
                buffer[b++] = line[i+1];
                i += 2;
                continue;
            }

            // End of token (space) if not inside quotes
            if (!is_single_quote && !is_double_quote && isspace(line[i])) break;

            buffer[b++] = line[i++];
        }
        buffer[b] = '\0';

        // Expand variables unless inside single quotes
        char expanded[1024];
        if (!is_single_quote)
            expand_variables(buffer, expanded);
        else
            strcpy(expanded, buffer);

        // Store token on heap
        args[token_index++] = strdup(expanded);
    }

    args[token_index] = NULL;
    return args;
}

/*
 * free_tokenized_args
 * -------------------
 * Frees a tokenized argument list created by tokenize_input.
 *
 * Frees:
 *   - Each individual token (char*)
 *   - The array itself (char**)
 */
void free_tokenized_args(char** args) {
    if (args == NULL) return;
    for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}