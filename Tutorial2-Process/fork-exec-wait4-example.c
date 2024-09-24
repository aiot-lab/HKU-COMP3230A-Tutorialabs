#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        // child process
        printf("child process %d\n", getpid());
        int i = 0;
        while(++i < 1e9);
        exit(0);
    } else {
        // parent process
        int status;
        struct rusage rusage;
        int ret = wait4(pid, &status, 0, &rusage);
        printf("child process %d terminated\n", pid);
        printf("pid: %d\n", ret);

        printf("user time: %.6f, system time: %.6f\n",
            rusage.ru_utime.tv_sec + rusage.ru_utime.tv_usec / 1000000.0,
            rusage.ru_stime.tv_sec + rusage.ru_stime.tv_usec / 1000000.0);
    }
    return 0;
}