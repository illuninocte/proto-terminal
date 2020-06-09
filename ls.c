#include <stdio.h>
#include <dirent.h>
#include "header/utils.h"

int main(int argc, char* argv[]) {
    DIR *d;
    struct dirent *dir;
    if(argc > 1)
        d = opendir(argv[1]);
    else
        d = opendir(".");
    int flag = 0;
    while((dir = readdir(d)) != NULL) {
        if(dir->d_name[0] != '.'){
            if(flag)
                printf(" ");
            if(dir->d_type == DT_DIR){
                printf(ANSI_COLOR_BLUE);
                printf("%s/", dir->d_name);
                printf(ANSI_COLOR_RESET);
            }
            else
                printf("%s", dir->d_name);
        }
        flag = 1;
    }
    printf("\n");
}