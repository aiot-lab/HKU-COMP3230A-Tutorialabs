#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

jmp_buf env; // Environment buffer

void sigfpe_handler(int signo)
{
    printf("SIGFPE caught!\n");
    longjmp(env, 1);
}

int main()
{
    signal(SIGFPE, sigfpe_handler);
    int rtn = setjmp(env);
    if (rtn == 0) {
        int a = 1;
        int b = 0;
        int c = a / b;
    } else {
        // 
        printf("SIGFPE handled!\n");
    }
    return 0;
}