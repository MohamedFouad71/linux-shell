#ifndef REDIRECT_EXECUTOR_H
#define REDIRECT_EXECUTOR_H

/*
 * Parses and executes command with output redirection.
 *
 * Args:
 *   redirect_type: type flag from redirected_or_appended()
 *   input_line: full command line with redirection
 */
void parse_redirect_or_append(int redirect_type, char *input_line);

#endif
