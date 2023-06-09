#include <fcntl.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

// prog tx
int main(int argc, char* argv[])
{
    if(argc < 2) {
	fprintf(stderr, "Error: Wrong number of arguments\n");
	exit(1);
    }

    int pid = atoi(argv[1]);
    printf("sending message to %d\n", pid);

    // verifica che il proc esista
    if(kill(pid,0) == -1) {
	fprintf(stderr, "Error: process does not exits\n");
	exit(1);
    }

    // invio dei dati al proc
    int64_t msg_conv = *((int64_t*)argv[2]);
    union sigval msg;
    msg.sival_ptr = (void*)msg_conv;

    if(sigqueue(pid, SIGUSR1, msg) == -1) {
	fprintf(stderr, "Error: couldn't send message\n");
	exit(1);
    }
    else
	printf("message sent\n");

    return 0;
}

