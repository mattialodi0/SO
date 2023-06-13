#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void signal_handler(int signum, siginfo_t *siginfo, void *ucontext)
{
    if (signum != SIGUSR1)
	exit(1);
    if (siginfo->si_code != SI_QUEUE)
	exit(1);

    union sigval value = siginfo->si_value;
    int64_t tmp = (int64_t)value.sival_ptr;
    char converted[8];
    for(int i=0; i<8; i++){
	converted[i]=tmp%256;
	tmp/=256;
    }
    printf("recived message: %s\n", converted);
}

// prog rx
int main(int argc, char* argv[])
{
    if(argc != 1) {
	fprintf(stderr, "Error: Wrong number of arguments\n");
	exit(1);
    }

    printf("rx pid: %d\n", (int)getpid());

    // ciclo di attesa dei segnali
    struct sigaction sigact;
    sigact.sa_flags = SA_SIGINFO;
    sigact.sa_sigaction = signal_handler;
    while(1){
	int ret = sigaction(SIGUSR1, &sigact, NULL);
    }

    return 0;
}

