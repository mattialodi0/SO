#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void nonest_symlink(char *linkpath) {
	struct stat buf;
	if (lstat(linkpath, &buf) == -1) {
		fprintf(stderr, "non riesco ad aprire %s\n", linkpath);
		return;
//		exit(-1);
	}
//	printf("ok\n");
	//se path è un link simbolico
	if (S_ISLNK(buf.st_mode)) {
		//verifica se punta ad un altro link simbolico
		char *filepath;
		filepath = realpath(linkpath, NULL);
		if(filepath == NULL) {
			fprintf(stderr, "Error while reading the link\n");
			exit(-1);
		}

		struct stat buf1;
		if (lstat(filepath, &buf1) == -1) {
			fprintf(stderr, "non riesco ad aprire %s\n", filepath);
			exit(-1);
		}
		if (S_ISLNK(buf1.st_mode)) {
			remove(filepath);
			printf("removed %s\n", filepath);
		}
		else printf("%s not pointing to a symlink\n", linkpath);

		free(filepath);
	}
//	else printf("the argument is not a path to a symlink\n");
}

int main(int argc, char *argv[]) {

	if(argc != 2) {
		fprintf(stderr, "Error, wrong number of arguments\n");
		exit(1);
	}

	//itera su tutti file della dir
	char path[1024];
	DIR *d;
  	struct dirent *dir;
	d = opendir(argv[1]);
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			printf("%s\n", dir->d_name);
			strcpy(path, argv[1]);
			strcat(path, "/");
			strcat(path, dir->d_name);
			nonest_symlink(path);
    		}
		closedir(d);
	}

	return 0;
}


