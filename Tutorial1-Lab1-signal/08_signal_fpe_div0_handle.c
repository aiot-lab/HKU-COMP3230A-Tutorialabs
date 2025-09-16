// file: singal_sync_div0.c
// description: signal handler example for FPE signal.
// #define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "COMP3230_signal.h"

void signal_handler(int signum) {
    printf("Caught signal %d (%s, %s)\n", signum, signal_list[signum], signal_des[signum]);
}

int main(int argc, char *argv[]) {
    // signalhandler_t: GNU extension uses this name, instead of sig_t
    sig_t pre_handler = signal(SIGFPE, signal_handler);
    if (pre_handler == SIG_ERR) {
        printf("Error: cannot set signal handler for SIGFPE\n");
        exit(1);
    } else {
        printf("Previous handler for SIGFPE: %p\n", pre_handler);
    }
    int a = 0;
    int b = 1;
    int c = b / a;
    // redefine signal handler, so that it will not exit
    
    return 0;
}
