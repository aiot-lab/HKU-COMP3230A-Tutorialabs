# Tutorialab-Lab1-signal
Answer to Tutorial 1 Lab 1&2
## 08_signal_fpe
Q1. Why it fails to override signal handler for SIGFPE?
A1. Although the signal handler for SIGFPE is overridden and execution of the signal handler is successful, the main program is still in a dead loop of "SIGFPE->handle->SIGFPE". One possible solution is to restore the environment of the main program before the possible SIGFPE occurs.
```c
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

jmp_buf env;

void sigfpe_handler(int signo)
{
    printf("SIGFPE caught!\n");
    longjmp(env, 1);
}

int main()
{
    signal(SIGFPE, sigfpe_handler);
    if (setjmp(env) == 0) {
        int a = 1;
        int b = 0;
        int c = a / b;
    } else {
        printf("SIGFPE handled!\n");
    }
    return 0;
}
```
