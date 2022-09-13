// file: 06_signal_sync_abrt.c
// description: signal handler example for ABRT signal.

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "COMP3230_signal.h"

// void signal_handler(int signum) {
//     printf("Caught signal %d (%s) - exiting now ...\n", signum, signal_list[signum]);
//     // exit(0);
// }

int main(int argc, char *argv[]) {
    // signal(SIGABRT, signal_handler);
    abort();
    // while(1) {
    //     printf("Hello World! run `kill -6 %d`\n", getpid());
    //     sleep(1);
    // }
    return 0;
}