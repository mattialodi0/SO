#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/inotify.h>

#define EVENT_SIZE  (sizeof(struct inotify_event))
#define BUF_LEN     (1024 * (EVENT_SIZE + 16))


void dircat(char *path1, char *path2) {
	int length, i = 0;
	int fd;
	int wd;
	char buffer[BUF_LEN];

	while(1) {
		fd = inotify_init();
		if (fd < 0) {
			perror("inotify_init");
		}

		wd = inotify_add_watch(fd, path1, IN_CREATE);
		length = read(fd, buffer, BUF_LEN);

		while (i < length) {
			struct inotify_event *event = (struct inotify_event *) &buffer[i];
		        if (event->len) {
				//se viene creato un nuovo file:
				if (event->mask & IN_CREATE) {
					printf("The file %s has been added to %s\n", event->name, path1);
					//aggiorna F
					FILE *f = fopen(path2, "a+");
					fprintf(f, "**** %s ****\n", event->name);

					//copia il contenuto
					char dfile[512];
					strcpy(dfile, path1);
					strcat(dfile, "/");
					strcat(dfile, event->name);
					FILE *df = fopen(dfile, "r");
					char c = fgetc(df);
					do {
						fputc(c, f);
						c = fgetc(df);
					} while(c != EOF);

					fprintf(f, "\n\n");
					fclose(f);

					//elimina il flie aggiunto
					remove(dfile);
					fclose(df);
				}
			}
			i += EVENT_SIZE + event->len;
		}
		i = 0;
	}

	inotify_rm_watch(fd, wd);
	close(fd);
}

int main(int argc, char *argv[]) {

	if(argc != 3) {
		fprintf(stderr, "Error, wrong number of arguments\n");
		exit(1);
	}

	dircat(argv[1], argv[2]);

	return 0;
}


