#include "../../include/cmdHistory.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void getHistoryFileDir(char* path, int size){
    // /prc/self/exe is a symbolic link to the executable file of the current process
    // readlink returns the contents of the symbolic link 
    // Which is the path to our program
    ssize_t length = readlink("/proc/self/exe", path, size);
    if(length == -1){   //Error happended while reading the link
        perror("Couldn't get history-file directory");
        return;
    }
    // Get a pointer to the last slash in the path
    char* lastSlash = strrchr(path,'/');
    // Convert the last slash to a null character, and neglect the executable name
    *lastSlash = '\0';
    // Add the path of the cmd_history to the path of the project
    strcat(path, "/data/cmd_history.txt");
}



void addCommandToHistory(char** args, char* pathToFile){
    // Open file for appending
    FILE* file = fopen(pathToFile, "a");

    // If an erorr occurred while oppening the file
    if(file == NULL){
        perror("Couldn't open file");
        return;
    }

    // Get the number of seconds since epoch
    time_t t = time(NULL);

    // Convert time into a human readable format using local time
    // localtime, takes a time_t value and returns a pointer to a tm struct
    struct tm* local = localtime(&t);

    // Print the time into history file
    // asctime, takes a pointer to a tm struct and converts it into string
    fputs(asctime(local),file);

    // Print the command and its arguments into history file
    int i = 0;
    while(args[i] != NULL){
        fputs(args[i],file);
        fputs(" ", file);
        ++i;
    }
    // Add a new line 
    fputs("\n", file);

    // Close the file and check if an errror ocurred or not
    int returnValue  = fclose(file);
    if(returnValue == EOF){
        perror("Couldn't close file");
    }
}