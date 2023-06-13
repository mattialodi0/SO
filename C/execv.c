#include  <unistd.h>
#include  <stdio.h>
#include  <string.h>
#include  <stdlib.h>

//prog di prova per lanciare ls con execv
int main(int argc, char *argv[]) {
	char binpath[] = {"/bin/"};
	strcat(binpath, argv[1]);

	execv(binpath, argv+1);

}

