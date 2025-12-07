#ifndef REDIRECT_HELPER_H
#define REDIRECT_HELPER_H

/*
 * Finds the first '>' character outside quotes and not escaped.
 *
 * Returns: pointer to '>' or NULL if not found
 */
char *find_redirection_operator(char *input_line);

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
int get_redirection_type(char *c);

#endif
