#include "trim.h"
#include <stdio.h>

#include <ctype.h>
#include <string.h>

// Finished
char *trim(char *str) {

    int i = 0;
    while (str[i] != '\0' && isspace((unsigned char)*str))
        str++;

    if (str[i] == '\0') return str;

    char *end = str + strlen(str) - 1;
    while (end != str && isspace((unsigned char)*end))
        end--;
    
    end[1] = '\0'; 

    return str;
}