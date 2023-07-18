#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("wrong num of args\n");
        return 1;
    }

    while (1)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            while (1)
            {
                if (execvp(argv[1], &argv[1]) == -1)
                    break;
            }
        }
        else
        {
            int st;
            waitpid(pid, &st, 0);
            if ((WIFEXITED(st) && WEXITSTATUS(st) != 0)|| WIFSIGNALED(st)) break;
        }
    }
}

// esame 22-9-7
