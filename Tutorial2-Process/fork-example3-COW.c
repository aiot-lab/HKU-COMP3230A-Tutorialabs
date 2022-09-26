#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
    int x = 0;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
      // child (new process)
      // addr of x is different from parent
		  printf("child: x @ %p\n", &x);
      printf("child: x = %d\n", ++x);
		  printf("child: x @ %p\n", &x);
    } else {
      // parent goes down this path (main)
      // addr of x is different from child
		  printf("parent: x @ %p\n", &x);
      printf("parent: x = %d\n", --x);
		  printf("parent: x @ %p\n", &x);
    }
    return 0;
}