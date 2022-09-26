#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

int main() {
  int pfd[2];
  pipe(pfd);
  if (fork() == 0) { //in child
    sleep(2); //force child to run later
    close(pfd[0]); //close the read end
    char buff[100];
    if (write(pfd[1], buff, 100) == -1) 
      printf("Child: Encountered write error\n");
  } else { //in parent
    close(pfd[0]); //close the read end
    printf("Press enter to close the program\n");
    getchar();
    int status;
    wait( & status);
    if (WIFSIGNALED(status))
      printf("Child process was terminated by signal %s\n", strsignal(WTERMSIG(status)));
  }
  return 0;
}