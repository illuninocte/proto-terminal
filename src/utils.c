#include "../header/utils.h"
#include <stdio.h>
#include <stdlib.h>

void erase_begin(char *str, int qtd){
    char *tmp = strdup(str+qtd);
    strcpy(str, tmp);
    free(tmp);
}

void update_program_path(char *prog_path, const char *cur_path){
    if(index_of(prog_path, "./") == 0) erase_begin(prog_path, 2);
    char tmp_dir[511];
    update_path(prog_path, cur_path, tmp_dir); tmp_dir[strlen(tmp_dir)-1] = 0;
    strcpy(prog_path, tmp_dir);
}
void update_path(const char *new_path, const char *cur_path, char *dest_path){
    if(new_path[0] == '/'){
        strcpy(dest_path, new_path);
    } else{
        int id = 0, cont_goback = 0;
        while(index_of(new_path+id, "../") == 0){
            id += 3;
            cont_goback++;
        }
        if(index_of(new_path+id, "..") == 0){
            id += 2;
            cont_goback++;
        }
        
        char *tmp_cur_path = strdup(cur_path);
        for(int i = strlen(tmp_cur_path) - 1; i >=0 && cont_goback >= 0; i--){
            if(tmp_cur_path[i] == '/'){
                cont_goback--;
                tmp_cur_path[i+1] = 0;
            }
        }
        
        strcpy(dest_path, tmp_cur_path);
        add(dest_path, new_path+id);
    }
    if(dest_path[strlen(dest_path)-1] != '/') add(dest_path, "/");
}

int index_of(const char* s, char* key) {
    if(strlen(s) >= strlen(key)){
        char *index = strstr(s, key);
        if(index)
            return s - index;
    }
    return -1;
}

void remove_line_break(char str[]){
    const int str_size = strlen(str);
    for(int i=0; i<str_size; i++){
        if(str[i] == '\n'){
            str[i] = 0;
            return;
        }
    }
}

void substr(int start, int sz, char* original, char* tmp){
    for(int i=0; i<sz; i++){
        tmp[i] = original[i+start];
    }
    tmp[sz] = 0;
}

void add(char* a, const char* b){
    int sz_a = strlen(a), sz_b = strlen(b);
    for(int i=0; i < sz_b; i++) {
        a[i+sz_a] = b[i];
    }
    a[sz_a + sz_b] = 0;
}
