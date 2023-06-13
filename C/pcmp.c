#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

int pcmp(char *path1,char *path2) {
    int f = 1;  //1 se i file sono =
    int c1;
    int c2;
    FILE* f1 = fopen(path1, "r");
    FILE* f2 = fopen(path2, "r");
    long int offset1 = 0;
    long int offset2 = 0;
    long int size1;
    long int size2;

    fseek(f1, 0L, SEEK_END);
    size1 = ftell(f1);
    fseek(f1, 0L, SEEK_SET);
    fseek(f2, 0L, SEEK_END);
    size2 = ftell(f2);
    fseek(f2, 0L, SEEK_SET);


    int pid = fork();
    if(pid == 0) {  //proc figlio
        offset1 = size1/2;
        offset2 = size2/2;
    }
    fseek(f1, offset1, SEEK_SET);
    fseek(f2, offset2, SEEK_SET);
    do {
        c1 = fgetc(f1);
        c2 = fgetc(f2);

        if(feof(f1) || feof(f2)) break;

        f = c1 == c2;
    }
    while(f == 1);

    fclose(f1);
    fclose(f2);

    return f;
}

int main(int argc, char *argv[]) {
    if(argc != 3) {
        perror("argv");
        exit(EXIT_FAILURE);
    }

    int f = pcmp(argv[1], argv[2]);
    if(f == 0) printf("%s %s differ\n", argv[1], argv[2]);

    return 0;
}
