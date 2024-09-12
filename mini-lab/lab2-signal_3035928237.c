// filename: lab2-signal.c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigusrHandler(int sig_num)
{
    // TODO2: Terminate the program when the SIGUSR1 signal is caught. (~1 line)
    exit(0);
}

int main()
{
    // TODO1: Set the signal handler for SIGUSR1 to the function sigusrHandler using the signal function. (~1 line)
    signal(SIGUSR1, sigusrHandler);
    // Write pid to a local file named pid.txt
    FILE *fp;
    fp = fopen("pid.txt", "w");
    fprintf(fp, "%d", getpid());
    fclose(fp);
    
    /* An infinite loop. */
    while(1) {
        printf("Still running...\n");
        sleep(1);
    }

    return 0;
}