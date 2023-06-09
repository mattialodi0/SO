/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/signalfd.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>


int main(int argc, char* argv[]){
	if(argc != 1) {	//controllo che il numero di parametri sia corretto
		printf("too many arguments\n");
		exit(EXIT_FAILURE);
	}

    printf("pid :%d\n", getpid());

    sigset_t sig;
    sigemptyset(&sig);
    sigaddset(&sig, SIGUSR1 | SIGUSR2);

    //si prepara a ricevere segnali
    int fd = signalfd(-1, &sig, 0);
    if(fd == -1) {	
		printf("Error in signalfd\n");
		exit(EXIT_FAILURE);
	}

    struct signalfd_siginfo ssi;
    while (1) {
        //aspetta un segnale
        ssize_t n = read(fd, &ssi, sizeof(ssi));
        if (n == -1) {	
		    printf("Error in read\n");
		    exit(EXIT_FAILURE);
	    }
        else if (n != sizeof(ssi)) {	
		    printf("Error in read, size\n");
		    exit(EXIT_FAILURE);
	    }

        if (ssi.ssi_signo == SIGUSR1 || ssi.ssi_signo == SIGUSR2) {
            char *filename;
            sprintf(filename, "%u", ssi.ssi_pid);
            char content[1024];
            sprintf(content, "%d %u", ssi.ssi_code, ssi.ssi_tid);

            printf("scritto%s\n%s\n", filename, content);
            //stampa 
            FILE *f = fopen(filename, "a");
            fprintf(f, content, strlen(content));
            fclose(f);
        }
    }
    close(fd);
    return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <fcntl.h>
#include <time.h>

#define MAX_FILENAME_SIZE 100

void handle_signal(int sig_num) {
    // Ottieni il PID del processo che ha inviato il segnale
    pid_t sender_pid = getpid();

    // Determina il nome del file basato sul PID del processo
    char filename[MAX_FILENAME_SIZE];
    snprintf(filename, MAX_FILENAME_SIZE, "%d.txt", sender_pid);

    // Apri il file in modalità append (se non esiste, viene creato)
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        exit(EXIT_FAILURE);
    }

    // Ottieni l'ora corrente
    time_t current_time;
    time(&current_time);
    struct tm *local_time = localtime(&current_time);

    // Scrivi le informazioni nel file
    fprintf(file, "Segnale ricevuto: %d\n", sig_num);
    fprintf(file, "Ora di ricezione: %s", asctime(local_time));
    fprintf(file, "----------------------------------\n");

    // Chiudi il file
    fclose(file);
}

int main() {
        printf("pid :%d\n", getpid());

    // Crea un insieme di segnali per SIGUSR1 e SIGUSR2
    sigset_t signal_set;
    sigemptyset(&signal_set);
    sigaddset(&signal_set, SIGUSR1);
    sigaddset(&signal_set, SIGUSR2);

    // Blocca i segnali SIGUSR1 e SIGUSR2
    sigprocmask(SIG_BLOCK, &signal_set, NULL);

    // Crea un file descriptor per i segnali SIGUSR1 e SIGUSR2
    int signal_fd = signalfd(-1, &signal_set, 0);
    if (signal_fd == -1) {
        perror("Errore nella creazione del signal_fd");
        exit(EXIT_FAILURE);
    }

    // Ciclo principale del programma
    while (1) {
        struct signalfd_siginfo sig_info;
        ssize_t num_bytes = read(signal_fd, &sig_info, sizeof(sig_info));
        if (num_bytes != sizeof(sig_info)) {
            perror("Errore nella lettura dal signal_fd");
            exit(EXIT_FAILURE);
        }

        // Gestisci i segnali ricevuti
        if (sig_info.ssi_signo == SIGUSR1 || sig_info.ssi_signo == SIGUSR2) {
            handle_signal(sig_info.ssi_signo);
        }
    }

    return 0;
}