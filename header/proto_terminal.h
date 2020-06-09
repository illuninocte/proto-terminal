#ifndef PROTO_TERMINAL_H
#define PROTO_TERMINAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include "utils.h"

const int max_dir_sz;
const int buffer_size;

void show_error(char* function, char* error);
void list(DIR*d, struct dirent *dir);
void change_directory(char *dir_path, char curr_dirr[], DIR **d);
void run(int len, char home[]);
void show_curr_path(char * curr);
void init();
int call_programming(int argc, char argv[][buffer_size], char* curr_dir);
int do_command(int argc, char argv[][buffer_size], char curr_dirr[], DIR **d, struct dirent **dir);
int built_in(int argc, char argv[][buffer_size], char curr_dirr[], DIR **d, struct dirent **dir);

#endif