#include "../../include/shell.h"

void cd(char** args) {
    static char prev_dir[1024] = "";

    char *target = args[1];

    // cd  → go HOME
    if (target == NULL) {
        target = getenv("HOME");
    }
    // cd ~
    else if (strcmp(target, "~") == 0) {
        target = getenv("HOME");
    }
    // cd -
    else if (strcmp(target, "-") == 0) {
        if (prev_dir[0] == '\0') {
            printf("No previous directory\n");
            return;
        }
        printf("%s\n", prev_dir); // like bash: print the old path
        target = prev_dir;
    }
    // cd ~/folder
    else if (target[0] == '~' && target[1] == '/') {
        static char temp[1024];
        snprintf(temp, sizeof(temp), "%s%s", getenv("HOME"), target + 1);
        target = temp;
    }

    // save current directory before changing
    char current[1024];
    getcwd(current, sizeof(current));

    if (chdir(target) != 0) {
        perror("cd");
        return;
    } else {
        strcpy(prev_dir, current);  // only update previous dir AFTER successful cd
    }
    return;
}