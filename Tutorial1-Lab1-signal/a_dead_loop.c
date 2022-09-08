// file: signal_async_int_default.c
// description: signal handler example for INTERUPT signal
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int i = 0;
    while (1) {
        // CTRL+Z: it will be suspended because it writes to stdout
        printf("(%d) sec. Infinity Loop: Exit on CTRL+C. Put to back on CTRL+Z. Use kill -9 %d to kill it.\n", ++i, getpid());
        fflush(stdout); // make sure the output is printed
        sleep(1);
    }
    return 0;
}