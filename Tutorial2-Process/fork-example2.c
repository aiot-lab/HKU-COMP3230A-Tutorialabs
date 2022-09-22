#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int i = 0;
int main(int argc, char *argv[]) {
	// int i = 0;
	fork();
	fork();
	fork();

	printf("Hello World! %i\n", ++i);

	return 0;
} // main
