#ifndef BUILTINS_H
#define BUILTINS_H

int is_builtins(char** args, char* line, char* historyFilePath);
void cd(char** args);
void about();
void help();
void help_specific(char *cmd_name);
void count(char** args);

#endif
