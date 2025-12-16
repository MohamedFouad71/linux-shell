/* src/builtins/help.c */
#include "../../include/shell.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    char *name;
    char *short_desc;
    char *usage;
    char *long_help;
}
 builtin_cmd_t;

builtin_cmd_t commands[] = {
    {
        "cd",
        "Change the shell working directory.",
        "cd [dir]",
        "Change the current directory to DIR. The default DIR is the value of the\n"
        "    HOME shell variable.\n\n"
        "    The variable CDPATH defines the search path for the directory containing\n"
        "    DIR. Alternative directory names in CDPATH are separated by a colon (:).\n"
        "    A null directory name is the same as the current directory.\n\n"
        "    Options:\n"
        "      - (dash)  Go to the previous working directory.\n"
        "      ~ (tilde) Go to the home directory.\n"
        "      ..        Go to the parent directory.\n\n"
        "    Exit Status:\n"
        "    Returns 0 if the directory is changed; non-zero otherwise."
    },
    {
        "exit",
        "Exit the shell.",
        "exit [n]",
        "Exits the shell with a status of N. If N is omitted, the exit status\n"
        "    is that of the last command executed."
    },
    {
        "help",
        "Display information about builtins.",
        "help [pattern]",
        "Display helpful information about builtin commands.\n"
        "    If PATTERN is specified, gives detailed help on all commands matching PATTERN,\n"
        "    otherwise the list of help topics is printed."
    },
    {
        "history",
        "Display the command history list.",
        "history",
        "Display the command history list with line numbers.\n"
        "    History is saved in data/cmd_history."
    },
    {
        "about",
        "Show information about Glitchy Shell.",
        "about",
        "Prints the version, developer names, and description of Glitchy Shell."
    },
    {
        "count",
        "Analyze file content (lines/words).",
        "count <filename>",
        "Counts lines, words, and characters in the specified file.\n"
        "    Arguments:\n"
        "      filename  The path to the file to analyze."
    },
    {NULL, NULL, NULL, NULL} 
};

void help_specific(char *cmd_name) {
    int i = 0;
    while (commands[i].name != NULL) {
        if (strcmp(commands[i].name, cmd_name) == 0) {
            printf("%s: %s\n", commands[i].name, commands[i].usage);
            printf("%s\n\n", commands[i].short_desc);
            printf("%s\n", commands[i].long_help);
            return;
        }
        i++;
    }
    printf("bash: help: no help topics match `%s'. Try `help'.\n", cmd_name);
}

void help() {
    printf("Glitchy Shell, version 1.0-release\n");
    printf("Type `help name' to find out more about the function `name'.\n\n");

    int i = 0;
    while (commands[i].name != NULL) {
        printf(" %-10s %s\n", commands[i].name, commands[i].short_desc);
        i++;
    }
    printf("\n");
}
