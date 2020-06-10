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
    command com;
    get_command(buffer, &com);
    printf("%d commands\n", com.qtd_prog);
    for(int i=0; i<com.qtd_prog; i++){
        printf("command %d (%d):", i, com.p[i].argc);
        for(int j=0; j<com.p[i].argc; j++){
            printf(" %s", com.p[i].argv[j]);
        }
        puts("@");
    }
    
    if(com.qtd_prog == 1 && strcmp(com.p[0].argv[0], "cd") == 0) {
        change_directory(com.p[0].argv[1], cur_path, d);
    } else if(com.qtd_prog == 1 && strcmp(com.p[0].argv[0], "ls") == 0) {
        if(com.p[0].argc == 1) list(cur_path);
        else {
            char tmp_dir[max_dir_sz];
            update_path(com.p[0].argv[1], cur_path, tmp_dir);
            list(tmp_dir);
        }
    } else if(com.qtd_prog == 1 && strcmp(com.p[0].argv[0], "pwd") == 0) {
        show_curr_path(cur_path);
    } else if(com.qtd_prog == 1 && strcmp(com.p[0].argv[0], "exit") == 0) {
        exit(0);
    } else{
        execute_command(&com, cur_path);
    }
}

char get_command(char* str, command *res) {
    char operator[] = "<>|&";
    int n = strlen(str);
    char tmp[n+1], sz = 0;
    int index = 0, id_prog = 0;
    res->qtd_prog = 0;
    for(int i=0; str[i];){
        if(str[i] == ' ' || str[i] == '\n'){
            if(sz == 1){
                int j;
                for(j=0; operator[j] && operator[j] != tmp[0]; j++);
                if(operator[j]){
                    res->op[id_prog] = tmp[0];
                    res->qtd_prog = ++id_prog;
                    res->p[id_prog].argc = index = 0;
                    sz = 0;

                    i++;
                    while(str[i] && (str[i] == ' ' || str[i] == '\n')) i++; // skip space
                    continue;
                }
            }

            tmp[sz] = 0;
            strcpy(res->p[id_prog].argv[index], tmp);
            res->p[id_prog].argc = ++index;
            sz = 0;
            i++;
            while(str[i] && (str[i] == ' ' || str[i] == '\n')) i++; // skip space
        } else{
            tmp[sz++] = str[i++];
        }
    }
    res->qtd_prog = ++id_prog;
    return 1;
}

int execute_command(command *com, const char *cur_path){
    program *p = (com->p);
    char qtd_prog = com->qtd_prog;
    char *op = com->op;
    for(int i=0; i<qtd_prog; i++){
        int rc = fork();
        if (rc < 0) {
            fprintf(stderr, "cannot fork\n");
            return 0;
        } else if (rc == 0) {
            
            char *myargs[buffer_size];
            for(int j=0; j<p[i].argc; j++) myargs[j] = strdup(p[i].argv[j]);
            update_program_path(myargs[0], cur_path);
            myargs[p[i].argc] = 0;

            int c = execvp(myargs[0], myargs);
            if(c < 0) show_error(myargs[0], "command not found");
            exit(0);
        } else {
            int wc = wait(NULL);
        }
    }
    return 1;
}