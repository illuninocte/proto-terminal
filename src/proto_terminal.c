#include "../header/proto_terminal.h"

const int max_dir_sz = 511;

void list(DIR*d, struct dirent *dir){
    int flag = 0;
    while((dir = readdir(d)) != NULL) {
        if(dir->d_name[0] != '.'){
            if(flag)
                printf(" ");
            if(dir->d_type == DT_DIR)
                printf("%s/", dir->d_name);
            else
                printf("%s", dir->d_name);
        }
        flag = 1;
    }
    printf("\n");
}

void show_error(char* function, char* error){
    printf("-proto-terminal: %s: %s\n", function, error);

}

void change_directory(char* dir_path, char* curr_dirr, DIR **d){
    DIR *new_d;
    char new_dir[max_dir_sz];
    if(dir_path[0] == '/'){
        strcpy(new_dir, dir_path);
    } else{
        strcpy(new_dir, curr_dirr);
        add(new_dir, dir_path);
    }
    new_d = opendir(new_dir);
    if(new_d){
        closedir((*d));
        (*d) = new_d;
        if(strcmp(dir_path, "..") != 0)
            strcpy(curr_dirr, new_dir);
        else{
            int i, curr_sz = strlen(curr_dirr);
            for(i=curr_sz-2; i>=0; i--)
                if(curr_dirr[i] == '/')
                    break;
            curr_dirr[i+1] = 0;
        }
        if(curr_dirr[strlen(curr_dirr)-1] != '/')
            add(curr_dirr, "/");
    } else {
        show_error("cd", "No such file or directory");
    }
}

void show_curr_dir(char home[], char curr_dirr[]){
    int home_index = index_of(curr_dirr, home);
    if(home_index == 0)
        printf("~/%s$ ", curr_dirr + strlen(home));
    else
        printf("%s$ ", curr_dirr);
}

void show_curr_path(char * curr){
    printf("%s\n", curr);
}

int do_command(char home[], char buffer[],char curr_dirr[], DIR **d, struct dirent **dir){
    remove_line_break(buffer);
    if(strcmp(buffer, "ls") == 0){
        list(*d, *dir);       
    } else if(strlen(buffer) > 1 && buffer[0] == 'c' && buffer[1] == 'd'){
        char path[255];
        substr(3, strlen(buffer)-3, buffer, path);
        change_directory(path, curr_dirr, d);
    }else if(strcmp(buffer, "pwd") == 0){
        show_curr_path(curr_dirr);
    } else if(strcmp(buffer, "exit") == 0){
        return 0;
    }
    show_curr_dir(home, curr_dirr);
}

void run(int len, char home[]){
    DIR *d;
    struct dirent *dir;
    if(len != -1)
        d = opendir(home);
    else
        d = opendir(".");
    if(d) {
        const int buffer_size = 255;
        char buffer[buffer_size], curr_dirr[max_dir_sz];
        strcpy(curr_dirr, home);
        show_curr_dir(home, curr_dirr);
        while(fgets(buffer, buffer_size, stdin)) {
            if(do_command(home, buffer, curr_dirr, &d, &dir) == 0)
                break;
        }   
        closedir(d);
    } else{
        printf("Canot open this directory\n");
    }
}

void init(){
    FILE *fp;
    char buff[255], home[255];
    int len_home = -1;
    fp = fopen(".terminal", "r");
    if(fp){
        while(fgets(buff, 255, (FILE*)fp)) {
            int t = index_of(buff, "entry_dir = ");
            if (t != -1) {
                t += strlen("entry_dir = ");
                strcpy(home, buff+t);
                len_home = strlen(home);
            }
        }
    } else{
        printf("File not founded.");
    }
    fclose(fp);
    run(len_home, home);
}