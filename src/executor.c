#include "../include/shell.h"
#include <string.h>   




//  execute_ls_with_color:

void execute_ls_with_color(char** args) {
    //color=auto
    int count = 0;
    while (args[count] != NULL)
     count++;

    //  allocate size(args + color_flag + NULL)
    char **new_args = malloc((count + 2) * sizeof(char*));
    
    new_args[0] = args[0]; // "ls"
    new_args[1] = "--color=auto";  // color flag bultin in "ls"

    
    for (int i = 1; i < count; i++) {
        new_args[i + 1] = args[i];
    }
    new_args[count + 1] = NULL;

    execvp(new_args[0], new_args);
    
    // error handling:
    perror("ls failed");
    free_tokenized_args(new_args);
    exit(1);
}






int execute_command(char** args, char* line) {
    


    pid_t pid = fork();

   // Handle the failure of fork
    if (pid == -1) {
        perror("Fork Failed");
        exit(1);
    }
   
    if (args[0] == NULL) {
        return 0;
    }

    // Child process will run this block
    if (pid == 0) {
       
        if (strcmp(args[0], "ls") == 0) {
           
            execute_ls_with_color(args);
           
        } 
        else {
           
            execvp(args[0], args);
           
        }

        perror("[Shell Error]: execvp failed in execute_command()");
        free_tokenized_args(args);
        free(line);
        exit(1);
        
    }

    // Wait for child to terminate and return its exit status
    int status = 0;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) return WEXITSTATUS(status);
    return status;
}
