#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;
    pid = fork();
    char *argsvec[] = {"ls", "-l", NULL};
    char *envp[] = {NULL};
    if (pid == 0) {
        // child process
        printf("I'm child process %d, I'm going to execute ls -l\n", getpid());
        // execvp("ls", argsvec);
        // execlp("ls", "ls", "-l", NULL);
        // execv("/bin/ls", argsvec);
        // execl("/bin/ls", "ls", "-l", NULL);
        // execle("/bin/ls", "ls", "-l", NULL, envp);
        // execve("/bin/ls", argsvec, envp);
        execvpe("ls", argsvec, envp);
        exit(0);
    } else {
        // parent process
        printf("I'm parent process %d, I'm waiting for child process %d\n", getpid(), pid);
        wait(&status);
        printf("child process %d terminated\n", pid);
    }
    return 0;
}