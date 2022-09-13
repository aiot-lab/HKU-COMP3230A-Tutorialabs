// file 18_signal_async_tstp.c
// description: signal handler example for TSTP signal
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "COMP3230_signal.h"

void signal_handler(int signum) {
    printf("Caught signal %d (%s), do nothing. Next time it will use default handler (SIG_DFL).\n", signum, signal_list[signum]);
    // use default signal handler
    signal(signum, SIG_DFL);
}

int main(int argc, char *argv[]) {
    signal(SIGTSTP, signal_handler);
    int i = 0;
    while (1) {
        printf("(%d) sec. Infinity Loop: Put to back on CTRL+Z. fg <job_id> to bring back. Use kill -9 %d to kill it.\n", ++i, getpid());
        fflush(stdout); // make sure the output is printed
        sleep(1);
    }
    return 0;
}

