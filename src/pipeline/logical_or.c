#include "../../include/shell.h"
#include "../../include/pipeline/logical_or.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int execute_logical_or(char *input_line, char* historyFilePath) {
    if (!input_line) return 0;

    // Collect segments split by || while respecting quotes
    char *s = input_line;
    int in_double = 0, in_single = 0;
    char *start = s;
    char **segments = malloc(16 * sizeof(char*));
    int seg_count = 0;

    for (char *c = s; ; ++c) {
        if (*c == '\\' && *(c+1) != '\0') { c++; continue; }
        if (*c == '"' && !in_single) { in_double = !in_double; }
        else if (*c == '\'' && !in_double) { in_single = !in_single; }

        if (!in_double && !in_single && *c == '|' && *(c+1) == '|') {
            int len = c - start;
            char *seg = malloc(len + 1);
            strncpy(seg, start, len);
            seg[len] = '\0';
            segments[seg_count++] = seg;
            start = c + 2; // skip ||
            c++; // advance past second |
        }
        if (*c == '\0') break;
    }

    // last segment
    if (start) {
        char *last = strdup(start);
        segments[seg_count++] = last;
    }

    int final_status = 0;
    for (int i = 0; i < seg_count; ++i) {
        // trim in place using trim() which returns pointer into string
        char *seg = segments[i];
        char *t = trim(seg);
        // duplicate trimmed portion so we can free original safely
        char *proc = strdup(t);

        int status = 0;
        if (has_pipe(proc)) {
            status = execute_pipeline(proc, historyFilePath);
        } else {
            int in_type = check_input_redirection(proc);
            if (in_type > 0) {
                execute_input_redirection(in_type, proc);
                status = 0; // unknown, assume success
            } else {
                int redir_type = redirected_or_appended(proc);
                if (redir_type) {
                    parse_redirect_or_append(redir_type, proc);
                    status = 0; // unknown
                } else {
                    char **args = tokenize_input(proc, " ");
                    if (args[0] == NULL) {
                        free_tokenized_args(args);
                        status = 0;
                    } else if (is_builtins(args, proc, historyFilePath)) {
                        // builtins do not currently return status; assume success
                        status = 0;
                    } else {
                        status = execute_command(args, proc);
                    }
                }
            }
        }

        free(proc);
        free(segments[i]);

        // If the previous command succeeded (status == 0), stop processing OR chain
        if (status == 0) {
            final_status = status;
            break;
        }
        final_status = status;
    }

    free(segments);
    return final_status;
}
