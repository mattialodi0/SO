#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
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
    struct tms* timer;
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
//	    else if(timer < 1000)
//		break;
	    else {
		times(timer);
		printf("time: %l", timer->tms_cstime);
	    }
	}
	else {
            perror("fork");
            exit(1);
        }
    }

    return 0;
}

