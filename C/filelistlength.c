#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        perror("argv");
        exit(EXIT_FAILURE);
    }

    // apertura del file di output
    FILE *f = fopen(argv[1], "w");

    // apertura della cartella
    DIR *d;
    struct dirent *dirent;
    d = opendir(".");
    if (d)
    {
        // ciclo su ogni file .c
        while ((dirent = readdir(d)) != NULL)
        {
            if (dirent->d_type == DT_REG && strncmp(dirent->d_name, argv[1], sizeof(argv[1])))  //cerca solo file regolari
            {
                int size;
                char name[256];

                sprintf(name, "%s", dirent->d_name);
                struct stat st;
                stat(name, &st);
                size = st.st_size;
                fprintf(f, "%d %s\n", size, name);
            }
        }
        closedir(d);
    }

    fclose(f);

    return 0;
}
