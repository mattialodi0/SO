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


void execname(char *path) {
	int length, i = 0;
	int fd;
	int wd;
	char buffer[BUF_LEN];

	while(1) {
		fd = inotify_init();
		if (fd < 0) {
			perror("inotify_init");
		}

		wd = inotify_add_watch(fd, path, IN_CREATE);
		length = read(fd, buffer, BUF_LEN);

		while (i < length) {
			struct inotify_event *event = (struct inotify_event *) &buffer[i];
		        if (event->len) {
				if (event->mask & IN_CREATE) {
					printf("The file %s was created\n", event->name);
					char file[1024];
					strcpy(file, path);
					strcat(file, "/");
					strcat(file, event->name);
					char cmd[2048];

					sprintf(cmd, "echo %s > '%s'", event->name, file);
					printf("echo %s > %s\n", event->name, file);
					remove(file);
					system(cmd);

					printf("Modified %s\n", event->name);
				}
			}
				i += EVENT_SIZE + event->len;
			}
	}

	inotify_rm_watch(fd, wd);
	close(fd);
}

int main(int argc, char *argv[]) {

	if(argc != 2) {
		fprintf(stderr, "Error, wrong number of arguments\n");
		exit(1);
	}

	execname(argv[1]);

	return 0;
}


