// file: lab3-process.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    pid_t pid = -1;
    printf("Before fork(). variable pid = %d, getpid()=%d, getppid()=%d\n", pid, getpid(), getppid());
    fflush(stdout);
    // TODO: Create a child process using fork() and store the return value in pid (~1 line)

    if (pid < 0) {
        fprintf(stderr, "fork() Failed");
        exit(-1);
    } else if (pid == 0) {
        // Child Process
        printf("Child Process. variable pid = %d, getpid()=%d, getppid()=%d\n", pid, getpid(), getppid());
        // TODO: Use exec() family to replace the current process image with "sleep", "20" (~1 line)
        
    } else {
        // TODO: Make the parent process wait for the child to complete (~1 line)
        
        printf("Parent Process. variable pid = %d, getpid()=%d, getppid()=%d\n", pid, getpid(), getppid());
    }
    return 0;
} // main