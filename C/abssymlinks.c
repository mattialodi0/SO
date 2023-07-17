#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void abssymlink(char *linkpath) {
	struct stat buf;
	if (lstat(linkpath, &buf) == -1) {
		fprintf(stderr, "non riesco ad aprire %s\n", linkpath);
		return;
	}
//	printf("ok\n");

	//se path è un link simbolico
	if (S_ISLNK(buf.st_mode)) {
                char filepath[1024];
		char *ptr;
                ptr = realpath(linkpath, filepath);
                if(ptr == NULL) {
                        fprintf(stderr, "Error while reading the link\n");
                        exit(-1);
                }

		//rimuove il vecchio link
		remove(linkpath);
		//crea il nuovo
//		system("ln -s absfilepath linkpath");
		symlink(filepath, linkpath);
		printf("changed %s\n",linkpath);
	}
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


