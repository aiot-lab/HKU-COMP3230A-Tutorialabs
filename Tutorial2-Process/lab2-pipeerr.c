#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void handler(int sig) {
    printf("receive signal %d\n", sig);
}

int main() {
  int pfd[2];
  signal(SIGPIPE, handler);
  pipe(pfd);
  if (fork() == 0) { //in child
    close(pfd[1]); //close the write end
    char buff[100];
    printf("Child: Read from pipe ...\n");
    int res = read(pfd[0], buff, 100);
    if (res == 0) {
      printf("Child: EOF is reached --No one holds the write end!!\n");
    }
  } else { //in parent
    close(pfd[1]); //close the write end
    printf("comment `close(pfd[1]); in parent` and try again\n");
    printf("Press enter to close the program\n");
    getchar();
  }
  return 0;
}