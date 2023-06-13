#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUFF_SIZE 1024

int main(int argc, char* argv[])
{
    if(argc == 1 || argc > 2) {
	fprintf(stderr, "Worng number of arguments\n");
    	exit(1);
    }
    char *myfifo = argv[1];

    if(mkfifo(myfifo, 0666) == -1) {
	perror("mkfifo");
	exit(1);
    }

    int fd = open(myfifo, O_RDONLY);
    if(fd == -1) {
	perror("open");
	exit(1);
    }

    while(1) {
        ssize_t sz;
        char buf[MAX_BUFF_SIZE];
        sz = read(fd, 50, buf);
        printf("%s", buf);

	if(sz == -1) {
	    perror("read");
	    exit(1);
	}
	else if(sz == 0) {
	    close(fd);
	    fd = open(myfifo, O_RDONLY);
	    if (fd == -1) {
                perror("open");
                exit(1);
            }
	}
	else {
	    buf[sz] = '\0';
            printf("%s", buf);

            if (strcmp(buf, "FINE\n") == 0) {
                break;
            }
	}
    }
    close(fd);
    unlink(myfifo);

    return 0;
}
