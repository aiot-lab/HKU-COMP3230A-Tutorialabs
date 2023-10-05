#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>


int main() {
  pid_t pid;

  pid = fork();

  if (pid < 0) { // fork error
    printf("fork: error no = %s\n", strerror(errno));
    exit(-1);
  } else if (pid == 0) { // child process
    printf("child: I am a child process, with pid %d\n", (int) getpid());
    return 1; // exit on my own
  } else { // parent process
    // siginfo_t is only a placeholder here, can also use siginto.si_pid to access pid
    siginfo_t info;
    int status;

    // wait for child to terminate and kept as zombie process
    // 1st param: P_ALL := any child process; P_PID := process specified as 2nd param
    // WNOWAIT: Leave the child in a waitable state;
    //    so that later another wait call can be used to again retrieve the child status information.
    // WEXITED: wait for processes that have exited
    int ret = waitid(P_ALL, 0, &info, WNOWAIT | WEXITED);  
    if (!ret) {
      printf("Child process %d has been turned into zombine status\n", (int) info.si_pid);
      waitpid(info.si_pid, &status, 0);
      if (WIFEXITED(status)) {
        printf("Child process %d's resource has exited with status %d\n", (int) info.si_pid, WEXITSTATUS(status));
      }
    } else {
      perror("waitid");
    }

    return 0;
  }
}
