# Useful C-language skills for OS course 
[TOC]
## How to use 
Document:
1. For basic Syntax of C language, please refer to [w3school: C Tutorial](https://www.w3schools.com/c/index.php)
2. Read the contents table and find the topic you are interested in.
3. Click the topic to jump to the corresponding section.
4. Read the content of the section

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

### file input and output
The file input and output are also commonly used input and output methods in C. The file input is used to read data from the file, and the file output is used to print data to the file. 

useful functions:
1. `fopen` function: open a file
2. `fclose` function: close a file, make sure to close the file after opening it.
3. `fread` function: read data from a file
4. `fwrite` function: write data to a file

(see 03-file-io.c for details)

### pointers
pointers are used to store the address of a variable. The address of a variable can be obtained by using the `&` operator. The value of a variable can be obtained by using the `*` operator. 

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    int a = 10;
    // int *p is a pointer to an integer
    // &a is the address of integer a
    int *p = &a;
    printf("a = %d, *p = %d\n", a, *p);
    *p = 20;
    printf("a = %d, *p = %d\n", a, *p);
    return 0;
}
```

### passing parameters by value and reference
In C, the parameters of a function are passed by value by default. If you want to pass the parameters by reference, you need to use the `&` operator to get the address of the parameter, and then pass the address to the function. 

(see 04-swap.c: swap0 is passed by value, swap1 & swap2 are passed by reference)

### dynamic memory allocation
The `malloc` function is used to dynamically allocate memory. The `free` function is used to free the memory allocated by `malloc`. To avoid memory leaks, you **must** call the `free` function to free the memory allocated by `malloc` after using it. 

Using `malloc`, we can dynamically allocate memory for an array. But we need to free the memory after using it. The address of the allocated memory will be returned as a pointer, and it locates in the process heap. (see ./Tutorial1-Lab2-virtual_memory/addr.c)


```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // allocate memory of an integer
    int *p = (int *)malloc(sizeof(int)); 
    *p = 10;
    printf("*p = %d\n", *p);
    free(p); // free the memory allocated by malloc
    return 0;
}
```

(see also 03-c_matrix_ptr.c, allocating memory for a matrix)

```c
// malloc the rows
matrix = (int **)malloc(n_row * sizeof(int *));
// malloc the columns
for (i = 0; i < n_row; i++) {
    matrix[i] = (int *)malloc(n_col * sizeof(int));
}
```

## GCC: a compiler for C language
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

## Makefile: a tool to automate the build process
An efficient way to compile multiple C files is to use a Makefile. The Makefile is a file that contains the compilation instructions for the program. The Makefile is a text file, and the file name is usually `Makefile`.

(see ./makefile)

For more information about Makefile, please refer to [Makefile Tutorial](https://makefiletutorial.com/). It's optional to learn Makefile, just for your reference.

## GDB: C debugger 
gdb is a debugger that can be used to debug C programs. It can be used to set breakpoints, step by step, and view the value of variables. 

Let's use VSCode integrated gdb to debug.

The necessary steps are:
1. Compile the code with the `-g` option.
2. Open the integrated terminal in VSCode.
3. Run the command `gdb ./hello` to start gdb.
4. Run the command `run` to run the program.
5. Run the command `break main` to set a breakpoint at the `main` function.
6. Run the command `continue` to continue the program.
7. Run the command `print a` to print the value of variable `a`.
8. Run the command `next` to step by step.
9. Run the command `quit` to quit gdb.

or you can use GUI to debug.(for beginners, I suggest you try at least once to use the integrated terminal to debug)
1. install `C/C++`, `C/C++ Extension Pack` and `C/C++ Runner` extensions in VScode.
2. the link here: [VScode: Debug C++/C](https://code.visualstudio.com/docs/cpp/cpp-debug) shows how to debug C/C++ in VScode.
3. (TODO if needed) For VScode debugging configurations, a note will be added to `./Useful-Docs/` folder. Please tell the TA if you fail to get the debugger working.
