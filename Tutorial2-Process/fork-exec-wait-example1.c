#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	pid_t pid = fork();

	if (pid < 0) {
		// Error Occurred
		fprintf(stderr, "fork() Failed");
		exit(-1);
	} else if (pid == 0) {
		// Child Process
		printf("Child Process.\n");
		execlp("/bin/ls", "ls", (char *) 0);
		printf("execlp() Failed");
		exit(-1);
	} else {
		// Parent Process
		wait(NULL);
		printf("Parent Process.\n");
		printf("\n");
	}

	return 0;

} // main
