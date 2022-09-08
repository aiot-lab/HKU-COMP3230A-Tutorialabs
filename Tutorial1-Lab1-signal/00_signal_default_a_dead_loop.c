// file: signal_async_int_default.c
// description: signal handler example for INTERUPT signal
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "COMP3230_signal.h"

void signal_handler(int signum){
    printf("Caught signal %d (%s, %s), do nothing. Next time it will be default handler.\n", signum, signal_list[signum], signal_des[signum]);
    // use default signal handler
    signal(signum, SIG_DFL);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);
    int i = 0;
    while (1) {
        printf("(%d) sec. Infinity Loop: Exit on CTRL+C. Put to back on CTRL+Z. Use kill -9 %d to kill it.\n", ++i, getpid());
        fflush(stdout); // make sure the output is printed
        sleep(1);
    }
    return 0;
}