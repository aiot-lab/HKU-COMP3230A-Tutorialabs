// file: 09_singal_async_kill.c
// description: signal handler example for KILL signal
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

#include "COMP3230_signal.h"

void signal_handler(int signum) {
    printf("Caught signal %d (%s) - exiting now ...\n", signum, signal_list[signum]);
}

int main(int argc, char *argv[]) {
    sig_t pre_handler = signal(SIGKILL, signal_handler);
    if (pre_handler == SIG_ERR) {
        printf("Error: cannot set signal handler for SIGKILL\n");
        exit(1);
    } else {
        printf("Previous handler for SIGKILL: %p\n", pre_handler);
    }
   int i = 0;
    while (1) {
        printf("(%d) sec. Infinity Loop: Exit on CTRL+C. Put to back on CTRL+Z. Use kill -9 %d to kill it.\n", ++i, getpid());
        sleep(1);
    }
    return 0;
}
