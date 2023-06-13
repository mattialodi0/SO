#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


void *threadfun(void *cmd) {
	system(cmd);
}

void exect(char *cmd) {
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, threadfun, (void*)cmd);
	pthread_join(thread_id, NULL);
}

int main(int argc, char* argv[]) {
	int i = 1;
	char cmd[1024];
	strcpy(cmd, " ");
	for(i; i < argc; i++) {
		if(strcmp(argv[i], "//") == 0) {
			exect(cmd);
			strcpy(cmd, " ");
		}
		else {
			strcat(cmd, argv[i]);
			strcat(cmd, " ");
		}
	}
	exect(cmd);
	strcpy(cmd, " ");

	printf("Terminated all commands\n");

	return(0);
}
