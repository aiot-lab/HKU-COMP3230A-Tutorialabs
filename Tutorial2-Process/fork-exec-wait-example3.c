#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	pid_t pid = fork();
	char * argVector[] = { "./HelloWorld", "HelloWorld", (char *) 0 };

	if (pid < 0) {
		// Error Occurred
		fprintf(stderr, "fork() Failed");
		exit(-1);
	} else if (pid == 0) {
		// Child Process
		printf("Child Process.\n");
		execvp("./HelloWorld", argVector);
		printf("execvp() Failed");
		exit(-1);
	} else {
		// Parent Process
		wait(NULL);
		printf("Parent Process.\n");
		printf("\n");
	}

	return 0;

} // main
