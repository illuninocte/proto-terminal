#include "../header/proto_terminal.h"

const int max_dir_sz = 511;
const int buffer_size = 255;

void list(char *path){
    DIR *d; d = opendir(path);
    if(!d){
        show_error("ls", "directory not found.");
        return;
    }
    int flag = 0;
    struct dirent *dir;
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
            flag = 1;
        }
    }
    printf("\n");
    closedir(d);
}

void show_error(char* function, char* error){
    printf("%s: %s\n", function, error);
}

void change_directory(char* new_path, char* cur_path, DIR **d){
    DIR *new_d;
    char dest_path[max_dir_sz];
    update_path(new_path, cur_path, dest_path);
    new_d = opendir(dest_path);
    if(new_d){
        closedir((*d));
        (*d) = new_d;
        strcpy(cur_path, dest_path);
    } else {
        show_error("cd", "No such file or directory");
    }
}


void show_curr_dir(char home[], char cur_path[]){
    int home_index = index_of(cur_path, home);
    printf(ANSI_COLOR_GREEN);
    if(home_index == 0)
        printf("~/%s$ ", cur_path + strlen(home));
    else
        printf("%s$ ", cur_path);
    printf(ANSI_COLOR_RESET);
}

void show_curr_path(char * curr){
    printf("%s\n", curr);
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
        while(len_home>=0 && home[len_home-1] != '/') len_home--;
        home[len_home] = 0;
    } else{
        printf("File not found.");
    }
    fclose(fp);
    run(len_home, home);
}

void run(int len, char home[]){
    DIR *d;
    struct dirent *dir;
    if(len != -1)
        d = opendir(home);
    else
        d = opendir(".");
    if(d) {
        char buffer[buffer_size], cur_path[max_dir_sz], argv[buffer_size][buffer_size];
        strcpy(cur_path, home);
        show_curr_dir(home, cur_path);
        int argc;
        while(fgets(buffer, buffer_size, stdin)) {
            do_command(buffer, cur_path, &d, &dir);
            show_curr_dir(home, cur_path);
        }   
        closedir(d);
    } else{
        printf("Canot open this directory\n");
    }
}

void do_command(char buffer[], char cur_path[], DIR **d, struct dirent **dir) {
    int argc; char argv[buffer_size][buffer_size];
    argc = split(buffer, ' ', argv);
    
    if(strcmp(argv[0], "cd") == 0) {
        change_directory(argv[1], cur_path, d);
    } else if(strcmp(argv[0], "ls") == 0) {
        if(argc == 1) list(cur_path);
        else {
            char tmp_dir[max_dir_sz];
            update_path(argv[1], cur_path, tmp_dir);
            list(tmp_dir);
        }
    } else if(strcmp(argv[0], "pwd") == 0) {
        show_curr_path(cur_path);
    } else if(strcmp(argv[0], "exit") == 0) {
        exit(0);
    } else{
        if(index_of(argv[0], "./") == 0) erase_begin(argv[0], 2);

        char tmp_dir[max_dir_sz];
        update_path(argv[0], cur_path, tmp_dir); tmp_dir[strlen(tmp_dir)-1] = 0;
        strcpy(argv[0], tmp_dir);
        puts(argv[0]);

        execute_program(argc, argv);
    }
}

int execute_program(int argc, char argv[][buffer_size]){

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "cannot fork\n");
        return 0;
    } else if (rc == 0) {
        char *myargs[buffer_size];
        for(int i=0; i<argc; i++) myargs[i] = strdup(argv[i]);

        int c = execvp(myargs[0], myargs);
        if(c < 0) show_error(myargs[0], "command not found");
        exit(0);
    } else {
        int wc = wait(NULL);
    }
    return 1;
}