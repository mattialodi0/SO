#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_DIM 1024

int main(int argc, char* argv[])
{
    if(argc < 2) {
	fprintf(stderr, "Error: Wrong number of arguments\n");
	exit(1);
    }

    int i;
    char cmd[MAX_DIM];
    strcpy(cmd, argv[1]);
    for(i=2; i<argc; i++) {
	strcat(cmd," ");
	strcat(cmd,argv[i]);
    }

    int status;
    while(1) {
	pid_t pid = fork();

	if(pid == 0) {
	    system(cmd);
//	    execvp(argv[1], &argv[1]);
	}
	else if(pid > 0) {
	    wait(&status);
	    if((WIFEXITED(status) && WEXITSTATUS(status) != 0)|| WIFSIGNALED(status)) {
		fprintf(stderr, "Process terminated with errors");
		break;
	    }
	}
	else {
            perror("fork");
            exit(1);
        }
/*	if (WIFSIGNALED(status)) {
            int signalNumber = WTERMSIG(status);
            printf("Il processo figlio è stato terminato a causa del segnale %d\n", signalNumber);
	    break;
        } else if (WIFEXITED(status)) {
            int exitStatus = WEXITSTATUS(status);
            printf("Il processo figlio è terminato normalmente con stato di uscita %d\n", exitStatus);
        }*/
    }

    return 0;
}

