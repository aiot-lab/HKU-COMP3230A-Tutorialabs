#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void sighup(int sig) {
    printf("CHILD: I have received a SIGHUP\n");
    signal(SIGHUP, SIG_DFL);  /* reset signal */
}

void sigint(int sig) {
    printf("CHILD: I have received a SIGINT\n");
    signal(SIGINT, SIG_DFL);  /* reset signal */
}

void sigquit(int sig) {
    printf("My DADDY has killed me!!\n");
    exit(0);
}

int main() {
    int pid;

    if ((pid = fork()) < 0) {
        exit(1);
    }

    if (pid == 0) {  /* child */
        signal(SIGHUP, sighup);
        signal(SIGINT, sigint);
        signal(SIGQUIT, sigquit);
        while (1) pause();
    } else {  /* parent */
        sleep(1);
        printf("\nPARENT: sending SIGHUP\n");
        kill(pid, SIGHUP);
        
        sleep(3);  /* pause for 3 seconds */
        printf("\nPARENT: sending SIGINT\n");
        kill(pid, SIGINT);
        
        sleep(3);  /* pause for 3 seconds */
        printf("\nPARENT: sending SIGQUIT\n");
        kill(pid, SIGQUIT);
        
        sleep(3);
    }

    printf("This is the END of program\n");
    return 0;
}
