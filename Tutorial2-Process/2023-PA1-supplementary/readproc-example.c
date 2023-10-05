#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	pid_t myid;
	char str[50];
	char comm[50]; // command name
	FILE * file;
	int foo_int; // placeholder for a number(4byte) we don't care in a fomrat string
	unsigned long long i, x;
	unsigned long h, ut, st;

	/* just run for some duration */
	for (i=0; i<1073741824; i += 2) {
		x *= i;
		if (x > 8589934589)
			x = 1;
	}

	myid = getpid();
  
    printf("My process ID is: %d\n", myid);
    printf("Please use another terminal to run this command to access the path: /proc/%d/stat -- 'cat /proc/%d/stat'\n", myid, myid);
    printf("Press enter to continue after you obtained the information\n");
    getchar();

	/* get my own procss statistics */
    // PA1 
	sprintf(str, "/proc/%d/stat", (int)myid);
	file = fopen(str, "r");
	if (file == NULL) {
		printf("Error in open my proc file\n");
		exit(0);
	}
	// read first 15 fields
	fscanf(file, "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu", &foo_int, comm, &str[0], &foo_int, &foo_int, &foo_int, &foo_int, &foo_int,
		(unsigned *)&foo_int, &h, &h, &h, &h, &ut, &st);
	fclose(file);
    
    // Use sysconf(_SC_CLK_TCK) to get "CPU clock ticks per second"
	printf("The number of clock ticks per second is: %ld\n", sysconf(_SC_CLK_TCK));
	
	printf("User time: %lf s\n", ut*1.0f/sysconf(_SC_CLK_TCK));
	printf("In system time: %lf s\n", st*1.0f/sysconf(_SC_CLK_TCK));
    printf("The process is in state: %c\n", str[0]);

    // Hints for PA1: 
	// read /proc/%d/status to find voluntary_ctxt_switches & nonvoluntary_ctxt_switches
	// Some useful functions: 
	// fopen: open a file
	// fgets: read a line from a file (split by \n)
	// strstr: find a substring in a string
	// strchr: find the first occurrence of a character in a string
	
	return 0;
}
