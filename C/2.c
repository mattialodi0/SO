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
    char *myfifo = "stdin2pipe";

    if(mkfifo(myfifo, 0666) == -1) {
	perror("mkfifo");
	exit(1);
    }

    int fd = open(myfifo, O_RDONLY);
    if(fd == -1) {
	perror("open");
	exit(1);
    }

    ssize_t sz1, sz2;
    char line1[MAX_BUFF_SIZE],line2[MAX_BUFF_SIZE];
    sz1 = read(fd, line1, sizeof(line1));
    sz2 = read(fd, line2, sizeof(line2));
    if(sz1 == -1 || sz2 == -1) {
	perror("read");
	exit(1);
    }

    //exec
    char cmd[2*MAX_BUFF_SIZE];
    strcpy(cmd, line1);
    strcat(cmd, " | ");
    strcat(cmd, line2);
    system(cmd);

    close(fd);
    unlink(myfifo);

    return 0;
}
