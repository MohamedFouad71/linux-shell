/* include/redirection/input_redirection.h */
#ifndef INPUT_REDIRECTION_H
#define INPUT_REDIRECTION_H

/*
 * Checks if the line contains input redirection ('<' or '<<')
 * Returns:
 * 0: No input redirection
 * 1: Input redirection '<'
 * 2: Here Document '<<'
 */
int check_input_redirection(char *line);

/*
 * Parses and executes a command with input redirection.
 * type: 1 for '<', 2 for '<<'
 */
void execute_input_redirection(int type, char *line);

#endif

