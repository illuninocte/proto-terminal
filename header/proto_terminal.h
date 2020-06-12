#ifndef PROTO_TERMINAL_H
#define PROTO_TERMINAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include "utils.h"
#include <fcntl.h>

const int max_dir_sz;
const int buffer_size;

typedef struct {
    char argc;
    char argv[20][200];
} program;

typedef struct{
    program p[20];
    char qtd_prog;
    char op[20];
} command;

void show_error(char* function, char* error);
void list(char *path);
void change_directory(char *dir_path, char curr_dirr[], DIR **d);
void run(int len, char home[]);
void show_curr_path(char * curr);
void init();
void do_command(char buffer[], char curr_dirr[], DIR **d, struct dirent **dir);
char get_command(char* str, command *res);
int execute_command(command *com, const char *cur_path);

#endif