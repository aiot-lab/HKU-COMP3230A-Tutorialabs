# Useful C-language skills for OS course 
## How to use 
Document:
1. Read the contents table and find the topic you are interested in.
2. Click the topic to jump to the corresponding section.
3. Read the content of the section

Code:
1. You can use `make all` command to compile all the code in the document.
2. You can use `make clean` command to delete all the compiled files.

## C language basics
This section will assume that you have a basic understanding of C language, and will not explain the basic grammar of C language. If you are not familiar with C language, you can refer to the following resources:

### main function
This is a simple program that prints "Hello World!" to the screen. It is a good starting point for learning C, and of course, for learning any programming language. 

```c
#include <stdio.h>
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
```
Please pay attention to the following points:
1. `#` is a preprocessor directive, which is used to include the header file `stdio.h`. The header file contains the declaration of the `printf` function. (use `gcc -E main.c` to see the effect of preprocessor)
2. The `main` function is the only entry point of the program. It is the first function that is called when the program is executed.
3. The `printf` function is used to print to the standard output(stdout). The `printf` function is defined in the `stdio.h` header file. So we need to include the `stdio.h` header file in the program.
4. The `return 0` statement is used to return a value from the `main` function. The value 0 indicates that the program is executed successfully.

Questions:
Q1: **To which function/program does`main` function return a value when it is executed in the command line?**

A1: `main` function returns a value to the command line.(Use `ps -ef` to see the process tree)
### standard input and output
The standard input and output are the most commonly used input and output methods in C. The standard input is used to read data from the keyboard, and the standard output is used to print data to the screen. 

```c
// file: 01-stdin-stdout.c
#include <stdio.h>
int main(int argc, char *argv[]) {
    int a, b;
    // scanf is a function to read data from the standard input(stdin)
    scanf("%d %d", &a, &b);
    // printf is a function to print to the standard output(stdout)
    printf("%d + %d = %d", a, b, a + b);
    return 0;
}
```


### GCC
gcc is a compiler that can compile C code into executable programs. It is the most commonly used compiler in the Linux system. 

gcc can accept multiple options. The most commonly used options are:
1. `-o`: Specify the name of the output file.
2. **`-g`: Generate debugging information.**
3. `-Wall`: Enable all warnings.
4. `-Werror`: Treat all warnings as errors.
5. `-O`: Specify the optimization level. 
6. `-I`: Specify the include path.
7. `-pthread`: Enable the pthread library. Will be used in OS multi-threading programming.

```c
int main(int argc, char *argv[]) {
    printf("Hello World");
    return 0;
}
```

```bash
# compile the code
gcc hello.c -o hello
# run the code
./hello
```

### Makefile
An efficient way to compile multiple C files is to use a Makefile. The Makefile is a file that contains the compilation instructions for the program. The Makefile is a text file, and the file name is usually `Makefile`.

(see makefile)

### gdb
gdb is a debugger that can be used to debug C programs. It can be used to set breakpoints, step by step, and view the value of variables. 

Let's use VSCode integrated gdb to debug.
