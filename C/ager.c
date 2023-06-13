#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>


void age(char *file) {
    struct stat attr;
    stat(file, &attr);
    //printf("Last modified time: %s", ctime(&attr.st_mtime));
    //printf("Last modified time: %ld\n", attr.st_mtime);
    long int time = attr.st_mtime;
    struct utimbuf newtime;

    //- 10 giorni in secondi
    time -= 864000;

    newtime.actime = attr.st_atime;
    newtime.modtime = time;

    if (utime(file, &newtime) < 0) {
        perror(file);
    }
}

void agerv() {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if(strcmp(".", dir->d_name) != 0 && strcmp("..", dir->d_name) != 0)
                age(dir->d_name);
        }
        closedir(d);
    }
}

void ager(int n, char *files[]) {
    int i = 0;
    for(i; i<n; i++) {
        age(files[i]);
    }
}

int main(int argc, char *argv[]) {

    if(argc == 1) {
        agerv();
    }
    else {
        ager(argc-1, argv+1);
    }

    return 0;
}
