#include "../../include/shell.h"

void count(char** args) {
    FILE* file = fopen(args[1], "r");

    // Error occured while openning file
    if(file == NULL){
        perror("Couldn't open file");
        return;
    }
    u64 lineCounter = 0, wordCounter = 0, charCounter = 0;
    char fileLine[MAXIMUM_LINE_LENGTH];

    // Read the file line by line
    while(fgets(fileLine, MAXIMUM_LINE_LENGTH, file) != NULL){
        ++lineCounter; // increment the number of lines
        
        // count number of characters in line
        size_t lineLength = strlen(fileLine);
        if(fileLine[lineLength-1] == '\n') --lineLength; // Don't count the \n character
        charCounter += lineLength;
        
        // Count number of words in line
        char* word = strtok(fileLine, " \n");
        while(word != NULL){
            ++wordCounter; 
            word = strtok(NULL, " \n");
        }
    }
    if(fclose(file) == EOF) 
        perror("Couldn't close file");
    // Print counters
    printf("%llu %llu %llu %s\n", lineCounter, wordCounter, charCounter, args[1]);
}
