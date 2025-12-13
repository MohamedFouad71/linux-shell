#ifndef TOKENIZER_H
#define TOKENIZER_H

char** tokenize_input(char* line, char *delim);
void free_tokenized_args(char** args);

#endif