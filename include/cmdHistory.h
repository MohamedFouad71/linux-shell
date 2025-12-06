#ifndef CMD_HISTORY_H_
#define CMD_HISTORY_H_


void addCommandToHistory(char** args, char* pathToFile);
void getHistoryFileDir(char* path, int size);


#endif // CMD_HISTORY_H_