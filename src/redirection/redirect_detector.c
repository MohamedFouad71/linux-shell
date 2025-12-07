#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "../../include/tokenizer.h"
#include "../../include/trim.h"
#include "../../include/redirection/redirect_detector.h"
#include "../../include/redirection/redirect_helper.h"
extern int get_redirection_type(char *c);

/*
 * Checks if input contains output redirection and returns type flag.
 *
 * Args: input command line
 *
 * Returns:
 *   0 - no redirection
 *   1 - '>'
 *   2 - '>>'
 *   3 - '2>'
 *   4 - '2>>'
 *   5 - '&>'
 *   6 - '&>>'
 */
int redirected_or_appended(char *line) {
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

        if (!in_single_quotes && !in_double_quotes && *c == '>') {
            extern int get_redirection_type(char *c);
            return get_redirection_type(c);
        }
    }

    return 0;
}
