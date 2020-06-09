#include "../header/proto_terminal.h"

const int max_dir_sz = 511;
const int buffer_size = 255;

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
    printf(ANSI_COLOR_GREEN);
    if(home_index == 0)
        printf("~/%s$ ", curr_dirr + strlen(home));
    else
        printf("%s$ ", curr_dirr);
    printf(ANSI_COLOR_RESET);
}

void show_curr_path(char * curr){
    printf("%s\n", curr);
}

int built_in(int argc, char argv[][buffer_size], char curr_dirr[], DIR **d, struct dirent **dir){
    if(strcmp(argv[0], "cd") == 0) {
        change_directory(argv[1], curr_dirr, d);   
    } else if(strcmp(argv[0], "ls") == 0) {
        strcpy(argv[0], "build/ls");
        strcpy(argv[argc++], curr_dirr);
        call_programming(argc, argv, curr_dirr);
    } else if(strcmp(argv[0], "pwd") == 0) {
        show_curr_path(curr_dirr);
    } else if(strcmp(argv[0], "exit") == 0) {
        return -1;
    } else{
        return 0;
    }
    return 1;
}

int do_command(int argc, char argv[][buffer_size], char curr_dirr[], DIR **d, struct dirent **dir) {
    int isBuilt = built_in(argc, argv, curr_dirr, d, dir);
    if(isBuilt == 1 || isBuilt == -1)
        return isBuilt;
    return call_programming(argc, argv, curr_dirr);
}

void run(int len, char home[]){
    DIR *d;
    struct dirent *dir;
    if(len != -1)
        d = opendir(home);
    else
        d = opendir(".");
    if(d) {
        char buffer[buffer_size], curr_dirr[max_dir_sz], argv[buffer_size][buffer_size];
        strcpy(curr_dirr, home);
        show_curr_dir(home, curr_dirr);
        int argc;
        while(fgets(buffer, buffer_size, stdin)) {
            argc = split(buffer, ' ', argv);
            if(do_command(argc, argv, curr_dirr, &d, &dir) == -1)
                break;
            show_curr_dir(home, curr_dirr);
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

int call_programming(int argc, char argv[][buffer_size], char* curr_dir){
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Cannot fork\n");
        return 0;
    } else if (rc == 0) {
        char *myargs[buffer_size];
        if(argv[0][0] == '.'){
            myargs[0] = strdup(curr_dir);
            add(myargs[0], argv[0]+2);
        } else{
            myargs[0] =  strdup(argv[0]);
        }
        for(int i=1; i<argc; i++)
            myargs[i] = strdup(argv[i]);
        myargs[argc] = NULL;
        int c = execvp(myargs[0], myargs);
        if(c < 0)
            show_error(myargs[0], "No such file or directory");
        exit(0);
    } else {
        int wc = wait(NULL);
    }
    return 1;
}