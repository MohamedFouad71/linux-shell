#include <stdio.h>
#include "../../include/pipeline/pipe_detector.h"

int has_pipe(char *line) {
    if (line == NULL) return 0;

    int in_double_quotes = 0;
    int in_single_quotes = 0;

    for (char *c = line; *c != '\0'; ++c) {
        if (*c == '\\' && *(c + 1) != '\0') {
            c++;  /* skip escaped char */
            continue;
        }

        if (!in_single_quotes && *c == '"') {
            in_double_quotes = !in_double_quotes;
            continue;
        }
        if (!in_double_quotes && *c == '\'') {
            in_single_quotes = !in_single_quotes;
           continue;
        }
        
        if (*c == '|') return 1;
    }

    return 0;
}