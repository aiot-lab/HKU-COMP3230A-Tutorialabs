#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	pid_t pid1, pid2;

	pid1 = fork();
	if (pid1 < 0) {
		// Error Occurred
		fprintf(stderr, "fork() Failed");
		exit(-1);
	} else if (pid1 == 0) {
		// Child Process 1
		pid2 = fork();
		if (pid2 < 0) {
			// Error Occurred
			fprintf(stderr, "fork() Failed");
			exit(-1);
		} else if (pid2 == 0) {
			// Child Process 2
			printf("Child Process 2\n");
		} else {
			// Child Process 1
			wait(NULL);
			printf("Child Process 1\n");
		}
	} else {
		// Parent Process
		wait(NULL);
		printf("Parent Process\n");
	}

	return 0;
} // main
