// file: 02_signal_async_int.c
// description: signal handler example for INTERUPT signal
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "COMP3230_signal.h"

void signal_handler(int signum) {
    static int count = 0;
    printf("Caught signal %d (%s) - %d time(s)\n", signum, signal_list[signum], ++count);
    if (count == 3) {
        printf(" - exiting now ... \n");
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    signal(SIGINT, signal_handler);
    while (1) {
        printf("Press CTRL+C 3 times to exit! Try to press CTRL+C\n");
        sleep(1);
    }
    return 0;
}
