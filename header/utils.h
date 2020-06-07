#ifndef UTILS_H
#define UTILS_H

#include <string.h>

void remove_line_break(char str[]);
int index_of(char* s, char* key);
void substr(int start, int sz, char* original, char* tmp);
void add(char* a, char* b);

#endif