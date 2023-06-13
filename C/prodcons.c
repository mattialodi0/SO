#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/eventfd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int buffer_count = 0;
int buffer_index = 0;
int running = 1;

int event_fd;

void* produttore(void* arg) {
    while (running) {
        // Genera un numero casuale
        int numero = rand() % 100;

        // Stampa il numero generato
        printf("Produttore: Generato numero %d\n", numero);

        // Metti il numero nel buffer condiviso
        buffer[buffer_index] = numero;
        buffer_index = (buffer_index + 1) % BUFFER_SIZE;
        buffer_count++;

        // Invia un segnale al consumatore
        uint64_t signal = 1;
        write(event_fd, &signal, sizeof(uint64_t));

        // Attendi un ritardo casuale
        usleep(rand() % 1000000);
    }

    pthread_exit(NULL);
}

void* consumatore(void* arg) {
    while (running) {
        // Attendi il segnale dal produttore
        uint64_t signal;
        read(event_fd, &signal, sizeof(uint64_t));

        // Leggi il numero dal buffer condiviso
        int numero = buffer[(buffer_index - buffer_count + BUFFER_SIZE) % BUFFER_SIZE];
        buffer_count--;

        // Stampa il numero letto
        printf("Consumatore: Letto numero %d\n", numero);

        // Attendi un ritardo casuale
        usleep(rand() % 1000000);
    }

    pthread_exit(NULL);
}

int main() {
    // Crea il descrittore dell'evento
    event_fd = eventfd(0, EFD_SEMAPHORE);
    if (event_fd == -1) {
        perror("Impossibile creare l'evento");
        exit(EXIT_FAILURE);
    }

    // Crea i thread produttore e consumatore
    pthread_t produttore_thread, consumatore_thread;
    pthread_create(&produttore_thread, NULL, produttore, NULL);
    pthread_create(&consumatore_thread, NULL, consumatore, NULL);

    // Attendi l'interruzione del programma (ad esempio, premi Ctrl+C)
    while (1);

    // Termina i thread e libera le risorse
    running = 0;
    pthread_join(produttore_thread, NULL);
    pthread_join(consumatore_thread, NULL);
    close(event_fd);

    return 0;
}
