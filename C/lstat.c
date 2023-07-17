#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        perror("argv");
        exit(EXIT_FAILURE);
    }

    // verifica file regolare
    struct stat fileStat;
    if (lstat(argv[1], &fileStat) == -1)
    {
        perror("Errore nella chiamata a lstat");
        return 1;
    }
    if (S_ISREG(fileStat.st_mode))
    {
        // conta i caratteri nell'n-esima col
        int chars = 0;

        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
            perror("Unable to open file!");
            exit(1);
        }

        // legge il file
        char chunk[128];
        while (fgets(chunk, sizeof(chunk), fp) != NULL)
        {
            int i = 0;
            while (chunk[i] != '\0')
            {
                i++;
            }
            if(i > atoi(argv[2])) chars++;
        }

        printf("%d characters in the %s col\n", chars, argv[2]);
        fclose(fp);
    }
}
