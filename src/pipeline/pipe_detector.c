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

/*
 * is_pipe_syntax_valid
 * --------------------
 * Checks that pipe characters ('|') are placed correctly (outside quotes):
 * - Not the first non-space character
 * - Not the last non-space character
 * - Not consecutive (e.g. "cmd || cmd")
 * Returns 1 if syntax is valid, 0 otherwise.
 */
int is_pipe_syntax_valid(char *line) {
    if (line == NULL) return 1;

    int in_double_quotes = 0;
    int in_single_quotes = 0;
    char *c = line;

    for (; *c != '\0'; ++c) {
        if (*c == '\\' && *(c + 1) != '\0') { c++; continue; }

        if (!in_single_quotes && *c == '"') { in_double_quotes = !in_double_quotes; continue; }
        if (!in_double_quotes && *c == '\'') { in_single_quotes = !in_single_quotes; continue; }

        if (*c == '|' && !in_double_quotes && !in_single_quotes) {
            // Check previous non-space character
            char *p = c - 1;
            while (p >= line && (*p == ' ' || *p == '\t')) p--;
            if (p < line) return 0; // nothing before '|'
            if (*p == '|') return 0; // consecutive pipes

            // Check next non-space character
            char *n = c + 1;
            while (*n != '\0' && (*n == ' ' || *n == '\t')) n++;
            if (*n == '\0') return 0; // nothing after '|'
            if (*n == '|') return 0; // consecutive pipes
        }
    }

    return 1;
}

/* Detect logical OR (||) outside quotes */
int has_logical_or(char *line) {
    if (line == NULL) return 0;

    int in_double_quotes = 0;
    int in_single_quotes = 0;

    for (char *c = line; *c != '\0'; ++c) {
        if (*c == '\\' && *(c + 1) != '\0') { c++; continue; }
        if (!in_single_quotes && *c == '"') { in_double_quotes = !in_double_quotes; continue; }
        if (!in_double_quotes && *c == '\'') { in_single_quotes = !in_single_quotes; continue; }

        if (*c == '|' && *(c + 1) == '|' && !in_double_quotes && !in_single_quotes) return 1;
    }

    return 0;
}