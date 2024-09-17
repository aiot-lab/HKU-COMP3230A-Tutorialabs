#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void handler(int sig) {
    int status;
    pid_t pid = wait(&status);
    printf("child %d terminated\n", pid);
}

int main() {
    signal(SIGCHLD, handler);
    pid_t pid = fork();
    if (pid == 0) {
        printf("I'm child %d, I'm going to terminate.\n", getpid());
        exit(0);
    } else {
        printf("I'm parent %d, I'm waiting for my child %d to terminate.\n", getpid(), pid);
        while (1) {
            sleep(1);
        }
    }
    return 0;
}