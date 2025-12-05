#include "../../include/shell.h"

void help() {
printf("\n--- My Simple Shell Help ---\n");
        
    printf("GNU bash, version 5.3.3(1)-release (x86_64-pc-linux-gnu)\n");
    printf("These shell commands are defined internally.  Type `help' to see this list.\n");
    printf("Type `help name' to find out more about the function `name'.\n");
    printf("Use `info bash' to find out more about the shell in general.\n");
    printf("Use `man -k' or `info' to find out more about commands not in this list.\n\n");
    printf("A star (*) next to a name means that the command is disabled.\n\n");


     
    printf("\n[1] Built-in Commands (Custom Implemented):\n");
    printf("  cd <path>        : Change directory. Supports (~ for home, - for prev, .. for up)\n");
    printf("  count <filename> : Analyze file (counts lines, words, and characters)\n");
    printf("  exit             : Terminate the shell session\n");
    printf("  help             : Display this help message\n");

    printf("\n[2] Common External Commands:\n");
    printf("  ls [-l] [-a]     : List directory contents (Long format, All files)\n");
    printf("  pwd              : Print current working directory path\n");
    printf("  mkdir <dirname>  : Create a new directory\n");
    printf("  rm <filename>    : Remove (delete) a file\n");
    printf("  rmdir <dirname>  : Remove an empty directory\n");
    printf("  cp <src> <dest>  : Copy file from source to destination\n");
    printf("  mv <src> <dest>  : Move or rename a file\n");
    printf("  cat <filename>   : Display file content\n");
    printf("  grep <txt> <file>: Search for a text pattern inside a file\n");
    printf("  clear            : Clear the terminal screen\n");
    
    printf("\nNote: You can execute ANY standard Linux command/program installed on this system.\n\n");
}