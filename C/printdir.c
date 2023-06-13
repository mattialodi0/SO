#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>


void printdir(char *dir, int level) {
    DIR *directory;
    struct dirent *entry;

    // Open the directory
    if((directory = opendir(dir)) == NULL) {
      	fprintf(stderr,"cannot open (%s) ",dir);
//        perror("Unable to open directory");
    }

    while ((entry = readdir(directory)) != NULL) {
	if(entry->d_type == DT_DIR) {
	    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
 	        int i;
  	        for(i=0; i<level; i++)
		    printf("\t");
                printf("%s\n", entry->d_name);

		char *new_dir = (char *)malloc(strlen(dir) + strlen(entry->d_name) + 1);
	        sprintf(new_dir, "%s/%s", dir, entry->d_name);
        	printdir(new_dir, level+1);
	        free(new_dir);
	    }
	}
    	else if (entry->d_type == DT_REG) {  // Regular file
	    int i;
	    for(i=0; i<level; i++)
		printf("\t");
            printf("%s\n", entry->d_name);
        }
     }

    closedir(directory);
}


int main(int argc, char *argv[]) {

	if(argc < 2 || argc > 3) {
		fprintf(stderr, "Error, wrong number of arguments\n");
		exit(1);
	}

	// visita la dir e ne stampa il contenuto
	printdir(argv[1], 0);

	return 0;
}

