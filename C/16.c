#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/timerfd.h>

void msleep(uint32_t milliseconds) {
    int timer_fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (timer_fd == -1) {
        perror("timerfd_create");
        exit(EXIT_FAILURE);
    }

    struct itimerspec timer_spec;
    timer_spec.it_interval.tv_sec = 0;
    timer_spec.it_interval.tv_nsec = 0;
    timer_spec.it_value.tv_sec = milliseconds / 1000;
    timer_spec.it_value.tv_nsec = (milliseconds % 1000) * 1000000;

    if (timerfd_settime(timer_fd, 0, &timer_spec, NULL) == -1) {
        perror("timerfd_settime");
        exit(EXIT_FAILURE);
    }

    uint64_t expirations;
    if (read(timer_fd, &expirations, sizeof(uint64_t)) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    close(timer_fd);
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        perror("argv");
        exit(EXIT_FAILURE);
    }

    printf("Sleeping for %d milliseconds...\n",atoi(argv[1]));
    msleep(atoi(argv[1]));
    printf("Done\n");

    return 0;
}