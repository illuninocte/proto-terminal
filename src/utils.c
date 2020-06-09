#include "../header/utils.h"
#include <stdio.h>

int index_of(char* s, char* key) {
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

void add(char* a, char* b){
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