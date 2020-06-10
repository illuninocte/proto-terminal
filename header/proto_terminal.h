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
void list(char *path);
void change_directory(char *dir_path, char curr_dirr[], DIR **d);
void run(int len, char home[]);
void show_curr_path(char * curr);
void init();
void do_command(char buffer[], char curr_dirr[], DIR **d, struct dirent **dir);
int execute_program(int argc, char argv[][buffer_size]);

#endif