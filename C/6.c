#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void invsymlink(char *linkpath) {
	struct stat buf;
	if (lstat(linkpath, &buf) == -1) {
		fprintf(stderr, "invsymlink: non riesco ad aprire %s\n", linkpath);
		exit(-1);
	}

	//se path è un link simbolico
	if (S_ISLNK(buf.st_mode)) {
		//rimuove il link corrente
		char *filepath;
		filepath = realpath(linkpath, NULL);
		if(filepath == NULL) {
			fprintf(stderr, "Error while reading the link\n");
			exit(-1);
		}

		if (remove(linkpath))
			fprintf(stderr, "remove failed!\n");
		if (rename(realpath, linkpath))
			fprintf(stderr, "rename failed!\n");
		if (symlink(linkpath, realpath))
			fprintf(stderr, "symlink failed!\n");

		free(filepath);
	}
	else printf("the argument is not a path to a symlink\n");

}

int main(int argc, char *argv[]) {

	if(argc != 2) {
		fprintf(stderr, "Error, wrong number of arguments\n");
		exit(1);
	}

	invsymlink(argv[1]);

	return 0;
}


