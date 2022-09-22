#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	pid_t pid = fork();

	if (pid < 0) {
		// Error Occurred
		fprintf(stderr, "fork() Failed");
		exit(-1);
	} else if (pid == 0) {
		// Child Process
		printf("Child Process.\n");
		printf("The process id of Child Process is: %d\n", getpid());
		printf("The parent process id of Child Process is: %d\n", getppid());
		printf("\n");
	} else {
		// Parent Process
		wait(NULL);
		printf("Parent Process.\n");
		printf("The process id of Parent Process is: %d\n", getpid());
		printf("The parent process id of Parent Process is: %d\n", getppid());
		printf("\n");
	}
	return 0;
} // main
