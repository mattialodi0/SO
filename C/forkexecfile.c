#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

void sigterm_handler(int signum) {
    // Gestione del segnale SIGTERM
    exit(0);
}

int execf(char *path) {

    pid_t child_pids[10];
    signal(SIGTERM, sigterm_handler);
    int num_commands = 0;
    char command[100];

    // legge i comandi 
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (fgets(command, sizeof(command), file) != NULL) {
        command[strcspn(command, "\n")] = '\0';

        pid_t pid = fork();
        if(pid == -1) {
            perror("Error forking");
            exit(EXIT_FAILURE);
        }
        else if(pid == 0) {
            // figlio, esegue un comando
            char *args[10];
            int i = 0;
            char *token = strtok(command, " ");

            while(token != NULL && i < 9) {
                args[i++] = token;
                token = strtok(NULL, " ");
            }
            args[i] = '\0';
            
            execvp(args[0], args);
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
        else {
            // padre
            child_pids[num_commands++] = pid;
        }
    }

    fclose(file);

    // ferma tutti dopo la prima terminazione
    int status;
    pid_t terminated_pid = wait(&status);

    for (int i = 0; i < num_commands; i++) {
        if (child_pids[i] != terminated_pid) {
            kill(child_pids[i], SIGTERM);
        }
    }
}


int main(int argc, char *argv[]) {

    if(argc == 2) {
        execf(argv[1]);
    }
    else {
        perror("argv");
        exit(EXIT_FAILURE);
    }

    return 0;
}
