// file: 01-gcc-basic.c
// description: try basic gcc command

// preprocessor, include stdio.h
#include <stdio.h>

// GCC is a compiler, it will compile the source code into machine code 
// (or object file, assembly code, etc. We will talk about them later)
// GCC basic usage: gcc -o <output> <input> <options>
// To compile: `gcc -o 01-gcc-basic 01-gcc-basic.c` 
// To run the executable file: `./01-gcc-basic`

// othe GCC options:
// -S: compile to assembly code
// -c: compile to object file
// -E: preprocess only
// -g: generate debug information
// -O: optimize the code
int main(int argc, char *argv[]) {
    printf("Congratulations! You have successfully compiled and run this program.");
    return 0;
}