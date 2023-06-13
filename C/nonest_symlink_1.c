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
		ssize_t nbytes, bufsiz;
		char *buf1;
		bufsiz = buf.st_size + 1;

		buf1 = malloc(bufsiz);
           if (buf1 == NULL) {
               perror("malloc");
               exit(EXIT_FAILURE);
           }

		nbytes = readlink(linkpath, buf1, bufsiz);
           if (nbytes == -1) {
               perror("readlink");
               exit(EXIT_FAILURE);
	           }

//		printf("'%s' points to '%.*s'\n", linkpath, (int)nbytes, buf1);

		struct stat buf2;
		if (lstat(buf1, &buf2) == -1) {
			fprintf(stderr, "non riesco ad aprire %s\n", buf1);
			exit(-1);
		}
		if (S_ISLNK(buf2.st_mode)) {
			remove(buf1);
			printf("removed %s\n", buf1);
		}
		else printf("%s not pointing to a symlink\n", linkpath);

		free(buf1);
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


