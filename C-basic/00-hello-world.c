// file: 00-hello-world.c
// description: hello world
#include <stdio.h>

// This is the entry point of the program, also called main function.
// argc: (optional) number of arguments from command line
// argv: (optional) array of arguments from command line
int main(int argc, char *argv[]) {
    // check input arguments
    if (argc != 2) {
        printf("Usage: %s <name>\n", argv[0]);
        return 1;
    }
    // scanf a string
    char name[100];
    printf("Please input course name: ");
    scanf("%s", name);

    // printf is a function to print to the standard output(stdout)
    printf("Hello %s! Welcome to %s", argv[1], name);
    return 0;
}