#include <fcntl.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dlfcn.h>


int main(int argc, char* argv[]){
	if(argc < 2){	//controllo che il numero di parametri sia corretto
		printf("ERR! Usage: %s PATH_TO_FOLDER [ARGS]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char *path = "/home/mattia/Desktop/prove/hw.so";
	void* lib = dlopen(path, RTLD_LOCAL | RTLD_LAZY);

	if(lib == NULL){
		printf("Err in dlopen\n");
		exit(EXIT_FAILURE);
	}

	void* fptr = dlsym(lib, "main");
	int iptr = ((int(*)(int,char*))fptr)(argc-1,argv+1);

	//(*fptr)(*iptr);

	dlclose(lib);
}
