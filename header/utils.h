#ifndef UTILS_H
#define UTILS_H

#include <string.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BLUE    "\x1b[34m"

void remove_line_break(char str[]);
int index_of(char* s, char* key);
void substr(int start, int sz, char* original, char* tmp);
void add(char* a, char* b);
int split(char* str, char separator, char res[][255]);

#endif