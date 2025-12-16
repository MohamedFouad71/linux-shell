#include "../include/shell.h"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void get_prompt(char* promptBuffer) {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    
    char hostname[1024];
    gethostname(hostname, sizeof(hostname));

    char *username = getenv("USER");

        // Format the prompt and store it in promptBuffer (add trailing space after $)
        sprintf(promptBuffer, "%s%s@%s%s:%s%s%s$ "
            ,ANSI_COLOR_GREEN,username, hostname, ANSI_COLOR_RESET,
            ANSI_COLOR_BLUE, cwd, ANSI_COLOR_RESET);
    
}
