#include "../include/shell.h"

void display_prompt() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    
    char hostname[1024];
    gethostname(hostname, sizeof(hostname));

    char *username = getenv("USER");
    printf(">%s@%s:%s$ ", username, hostname, cwd);
}
