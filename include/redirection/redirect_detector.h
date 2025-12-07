#ifndef REDIRECT_DETECTOR_H
#define REDIRECT_DETECTOR_H

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
int redirected_or_appended(char *line);

#endif
