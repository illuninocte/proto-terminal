#include "header/proto_terminal.h"

int main(int argc, char* argv[]) {    
    DIR *d;
    struct dirent *dir;
    if(argc > 1)
        d = opendir(argv[1]);
    else
        d = opendir(".");
    list(d, dir);
    return 0;
}