#include "../header/utils.h"
#include <stdio.h>
#include <stdlib.h>

void update_path(const char *new_path, const char *cur_path, char *dest_path){
    if(new_path[0] == '/'){
        strcpy(dest_path, new_path);
        return;
    }
    
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

int split(char* str, char separator, char res[][255]) {
    int index = 0, i=0, sz = 0;
    while(str[i]){
        if(str[i] == separator || str[i] == '\n') {
            res[index][sz] = 0;
            sz = 0;
            index++;
        } else{
            res[index][sz] = str[i];
            sz++;
        }
        i++;
    }
    res[index][sz] = 0;
    return index + (str[i-1] != '\n');
}