#include "../../include/cmdHistory.h"
#include <stdio.h>
#include <time.h>


void addCommandToHistory(char** args){
    // Open file for appending
    FILE* file = fopen("data/cmd_history.txt", "a");

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