#ifndef PROTO_TERMINAL_H
#define PROTO_TERMINAL_H

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

const int max_dir_sz;

void show_error(char* function, char* error);
void list(DIR*d, struct dirent *dir);
void change_directory(char *dir_path, char curr_dirr[], DIR **d);
void run(int len, char home[]);
void show_curr_path(char * curr);
void init();

#endif