#include "../../include/shell.h"

void count(char** args) {
    if (args[1] == NULL) {
        // No file provided
        fprintf(stderr, "count: missing file operand\n");
        return;
    }
    // Totals (only sum successful files)
    u64 total_lines = 0, total_words = 0, total_chars = 0;
    int files_counted = 0;

    // Process each filename passed as argument
    for (int i = 1; args[i] != NULL; ++i) {
        FILE* file = fopen(args[i], "r");
        if (file == NULL) {
            perror("Couldn't open file");
            continue;
        }

        u64 lineCounter = 0, wordCounter = 0, charCounter = 0;
        char fileLine[MAXIMUM_LINE_LENGTH];

        // Read the file line by line
        while (fgets(fileLine, MAXIMUM_LINE_LENGTH, file) != NULL) {
            ++lineCounter; // increment the number of lines

            // count number of characters in line
            size_t lineLength = strlen(fileLine);
            if (lineLength > 0 && fileLine[lineLength-1] == '\n') --lineLength; // Don't count the \n character
            charCounter += lineLength;

            // Count number of words in line
            char* tokenized = strdup(fileLine);
            char* word = strtok(tokenized, " \n");
            while (word != NULL) {
                ++wordCounter;
                word = strtok(NULL, " \n");
            }
            free(tokenized);
        }

        if (fclose(file) == EOF)
            perror("Couldn't close file");

        // Print counters for this file
        printf("%llu %llu %llu %s\n", lineCounter, wordCounter, charCounter, args[i]);

        // Accumulate totals for successfully processed files
        total_lines += lineCounter;
        total_words += wordCounter;
        total_chars += charCounter;
        files_counted++;
    }

    // If more than one file was counted, print a total line (like wc)
    if (files_counted > 1) {
        printf("%llu %llu %llu total\n", total_lines, total_words, total_chars);
    }
}
