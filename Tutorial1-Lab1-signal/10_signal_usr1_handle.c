#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// use sigaction to handle SIGUSR1
void handler(int sig, siginfo_t *info, void *ucontext) {
    printf("receive signal %d from %d\n", sig, info->si_pid);
}
int main() {
    // sigaction
    struct sigaction act;
    act.sa_flags = SA_SIGINFO; // set the flag to allow the handler to receive more information    
    act.sa_handler = handler;
    sigaction(SIGUSR1, &act, NULL);

    // signal
    // signal(SIGUSR1, handler);

    while (1) {
        printf("I'm process %d, waiting SIGUSR1.\n", getpid());
        sleep(1);
    }
    return 0;
}