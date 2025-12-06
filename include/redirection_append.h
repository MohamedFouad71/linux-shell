#ifndef REDIRECTION_APPEND_H
#define REDIRECTION_APPEND_H
#include <string.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>     // for open(), O_CREAT, O_TRUNC…
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int is_redirected_or_appended(char* line);
void parse_redirect_or_append(int redirect_or_append, char *input_line);


#endif