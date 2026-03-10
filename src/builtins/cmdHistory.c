#include "../../include/shell.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void getHistoryFileDir(char* path, int size){
    // 1. Pass (size - 1) to leave exactly one byte for the null terminator
    ssize_t length = readlink("/proc/self/exe", path, size - 1);
    
    if(length == -1){   
        perror("Couldn't get history-file directory");
        return;
    }
    
    // 2. Manually null-terminate the string!
    path[length] = '\0';

    char* lastSlash = strrchr(path,'/');
    
    // 3. Good practice: Check if strrchr actually found a slash before dereferencing
    if (lastSlash != NULL) {
        *lastSlash = '\0';
    }
    
    strcat(path, "/data/cmd_history");
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

void printHistory(char* pathToFile){
    FILE* file = fopen(pathToFile,"r");
    char line[MAXIMUM_LINE_LENGTH];
    while(fgets(line, MAXIMUM_LINE_LENGTH,file) != NULL){
        printf("%s",line);
    }
    int returnValue  = fclose(file);
    if(returnValue == EOF){
        perror("Couldn't close file");
    }
}