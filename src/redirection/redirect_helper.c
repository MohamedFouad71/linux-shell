#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include "../../include/redirection/redirect_helper.h"

/*
 * Determines the redirection type based on character at pointer c.
 * Caller must ensure c points to a '>' character and c-1 is valid.
 *
 * Returns:
 *   1 - '>' (stdout overwrite)
 *   2 - '>>' (stdout append)
 *   3 - '2>' (stderr overwrite)
 *   4 - '2>>' (stderr append)
 *   5 - '&>' (both overwrite)
 *   6 - '&>>' (both append)
 */
int get_redirection_type(char *c) {
    int is_append = (*(c + 1) == '>') ? 1 : 0;

    if (*(c - 1) == '2') return is_append ? 4 : 3;
    if (*(c - 1) == '&') return is_append ? 6 : 5;
    return is_append ? 2 : 1;
}

/*
 * Finds the first '>' character outside quotes and not escaped.
 *
 * Returns: pointer to '>' or NULL if not found
 */
char *find_redirection_operator(char *input_line) {
    int in_double = 0, in_single = 0;
    
    for (char *p = input_line; *p; ++p) {
        if (*p == '\\' && *(p + 1) != '\0') {
            p++;  /* skip escaped char */
            continue;
        }
        
        if (!in_single && *p == '"') {
            in_double = !in_double;
            continue;
        }
        if (!in_double && *p == '\'') {
            in_single = !in_single;
            continue;
        }
        
        if (!in_single && !in_double && *p == '>') {
            return p;
        }
    }
    return NULL;
}
