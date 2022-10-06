# C String process
### Contents
String processing is always a common task in programming, and especially in a commandline interface. This document aims to introduce how to process a string in C, including:

0) Basic concepts and how to - 
1) use string.h head file to get string length, copy, compare and split.
2) use a format string
3) convert error num/signal num to a readable message. 

### How to use
1. Please read the document from top to bottom, and try to understand the code and run the code by yourselves. For more other details about C, you can visit any C tutorial website, like [w3school](https://www.w3schools.com/c/index.php) or send your questions to TAs.
2. To run the code in this doc, you can either copy them as a new C file, or use `md-auto-compiler.sh` provided in the same directory to automatically compile example code from given range of doc lines (open it in your editor to get line number).

./md-auto-compiler.sh usage:
```bash
#./md-auto-compiler.sh <file> <start line> <end line> 
./md-auto-compiler.sh 05-c-string.md 40 59
```

## 0.Basic concepts of C string
### 0.0 char in C

#### ASCII
Char is an unsigned one-byte(0-255) data type in C language, which can store a character. C Language uses ASCII to represent characters. For example, the character 'a' is represented by 97 in ASCII. The character 'A' is represented by 65 in ASCII. (See ASCII Table below)

#### special characters
Specially, the value 0 represents the null character '\0', and is used to indicate the end of a string. Also, there are other special characters, such as '\n'(10), '\t'(9), '\r'(13), etc. For more information, please refer to 

![ASCII](https://www.asciitable.com/asciifull.gif)

### 0.1 String in C
In C, a string is represented by a char array. For example, the string "hello" is represented by the char array `{'h', 'e', 'l', 'l', 'o', '\0'}`. The last element of the char array is `\0`, which is the end of the string. The following example shows you how to define a string in C.
You can initialize a string by using 
1. a string literal, which is a sequence of characters enclosed in double quotes.
2. a character array, which is a sequence of characters enclosed in curly braces.
3. char constants at each index of the array.

The following example shows you how to define a string using "string literal", 
```c
#include <stdio.h>
#include <stdlib.h>
void captialize_string(char *str){
    int i = 0;
    while(str[i] != '\0'){
        if(str[i] >= 'a' && str[i] <= 'z'){
            str[i] = str[i] - 'a' + 'A';
        }
        i++;
    }
}

int main() {
    char str1[] = "hello"; // define a string using string literal
    char str2[6] = {'h', 'e', 'l', 'l', 'o', '\0'}; // define a string
    char *str3;
    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);

    str3 = (char *)malloc(6 * sizeof(char));
    str3[0] = 'h';
    str3[1] = 'e';
    str3[2] = 'l';
    str3[3] = 'l';
    str3[4] = 'o';
    str3[5] = '\0';
    printf("str3: %s\n", str3);

    captialize_string(str3);
    printf("capitalized str3: %s\n", str3);
    free(str3);
    return 0;
}
```
## 1. String operations
As C string is represented by a char array, we can use the same ideas as array to process a string. For example, we can use `for` loop to traverse a string. Besides, there are some useful in C header file `string.h` to help us process a string. The following sections will introduce some useful functions in `string.h`.

### 1.1 String length: `strlen()`
The length of a string is the number of characters in the string. We can use `strlen()` function in `string.h` to get the length of a string. This function takes in a char pointer as input **char-string header** addr, and returns the length of the string, i.e. how many non-`\0` characters from the beginning **char-string header** to the first `\0`(exclusive). The following example shows you how to use `strlen()` function.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "hello";
    printf("Use char str[] = \"hello\" to define a string\n");
    printf("length of %s is %lu\n", str, strlen(str));

    char str2[6] = {'h', 'e', 'l', '\0', 'o', '\0'};
    printf("Use char str2[6] = {'h', 'e', 'l', 'l', 'o', '\\0'} to define a string\n");
    printf("length of %s is %lu\n", str2, strlen(str2));

    // If the string is not ended with '\0', the result is undefined
    char str3[] = {'1'};
    printf("Use char str3[] = {'1'} to define a string, which is not ended with '\\0'\n");
    printf("length of %s is %lu\n", str3, strlen(str3));
    return 0;
}
```
Please note that the length of a string does not include the `\0` character. The length of the string "hello" is 5, not 6.

### 1.2 String copy: `strcpy()`
We can use `strcpy(char *dest, const char *src)` and `strncpy(char *dest, const char *src, size_t n)` function in `string.h` to copy a string. 

The `strcpy()` function takes in two char pointers as input:
1. the first one is the *char-string header addr* of the destination string
2. the second one is the *char-string header addr* of the source string. 

The `strcpy()` function copies the source string to the destination string, and returns the *char-string header addr* of the destination string. 

```c
The following example shows you how to copy a string.
```c
#include <stdio.h>
#include <string.h>

int main() {
    char str1[] = "hello";
    char str2[6];
    strcpy(str2, str1);
    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);
    return 0;
}
```
### 1.3 String compare: `strcmp()`
`strcmp(const char *str1, const char *str2)` function in `string.h` compares two strings. The `strcmp()` function takes in two char pointers as input, comparing the two strings char by char. If the two strings are the same, the `strcmp()` function returns 0. Otherwise, the first different characters (or NULL if the other is shorter) in the two strings (namely, a1 - a2) is returned. The following example shows you how to use `strcmp()` function.
```c
#include <stdio.h>
#include <string.h>

int main() {
    char str1[] = "COMP3230A";
    char str2[] = "COMP3230a";
    char str3[] = "COMP3230";

    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);
    printf("str3: %s\n", str3);

    printf("strcmp(str1, str2): %d\n", strcmp(str1, str2));
    printf("strcmp(str1, str3): %d\n", strcmp(str1, str3));
    printf("strcmp(str3, str2): %d\n", strcmp(str3, str2));
    
    return 0;
}
```

### 1.4 String Split: `strtok()`
`strtok(char *str, const char *delim)` function in `string.h` breaks a string into a sequence of tokens. The `strtok()` function takes in two char pointers as input, the first one is the *char-string header addr* of the string to be broken, and the second one is the *char-string header addr* of the **delimiters set** (as a string literal, e.g. "\t\n" means use both '\t' and '\n' as delimiters). 

Please note that, strtok() is a stateful function, which means that it keeps track of the last token it found and the rest of the string. 

1. The first call of `strtok(str, delim)` function returns a pointer to the first token found in the string. 
2. The following calls of `strtok(NULL, delim)` function returns a pointer to the next token found in the string. (the string should be **NULL**, not the original string), and `strtok()` function uses static variables to store the information of the previous call of `strtok()` function.

The following example shows you how to use `strtok()` function.
```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Do you \twant to \tbuild \ta snowman?\nCome on let's go and play\nI never see you anymore\nCome out the door\nIt's like you've gone away\nWe used to be best buddies\nAnd now we're not\nI wish you would tell me why\nDo you want to build a snowman?\nIt doesn't have to be a snowman.\n";
    char *token;
    int line = 1;
    printf("str: %s\n", str);
    char *delim = " ";
    printf("delim: %s\n", delim);
    token = strtok(str, delim);
    while (token != NULL) {
        printf("line %d: %s\n", line++, token);
        token = strtok(NULL, delim);
    }
    return 0;
}
```

## 2. Format string
In previous C-Basics, we know how to use `printf()` function to print a format string. A format string is a string that contains one or more format specifiers. The format specifiers are used to specify how to print the corresponding variable. You can tell `printf()` function to print a variable in different ways, such as:
1. as an integer, in decimal(`%d`), octal(`%o`), or hexadecimal(`%x`).
2. as a float, specifying number of digits after the decimal point, e.g. `%.2f` means print the float with 2 digits after the decimal point.
3. as a character(`%c`), specifying the width of the field, e.g. `%10c` means print the character with a field width of 10-character-width.
4. as a string(`%s`), interpreting the variable as a pointer to a char-string header addr.

The following example is a format table, which shows you how to use format specifiers to print variables

```c
#include <stdio.h>

int main() {
    char table_name[] = "Example Table";
    char *table_header[] = {"ID", "Name", "Score", "Grade"};
    int student_id[] = {001, 002, 003, 004, 005};
    char student_name[][20] = {"John", "Mary", "Tom", "Alice", "Bob"};
    float student_score[] = {80.5, 90.5, 70.5, 60.5, 50.5};
    char student_grade[] = {'A', 'A', 'B', 'C', 'D'};
    
    // format string (width: 10, decimal: 2) 
    char row_format[] = "%10d%10s%10.2f%10c\n";
    
    int i;
    printf("Table name: %s\n", table_name);
    printf("%10s%10s%10s%10s\n", table_header[0], table_header[1], table_header[2], table_header[3]);
    for (i = 0; i < 5; i++) {
        printf(row_format, student_id[i], student_name[i], student_score[i], student_grade[i]);
    }

    return 0;    
}
```

### Form a format string: `sprintf()` & `fprintf()`
`sprintf(char *str, const char *format, ...)` function in `stdio.h` is used to write formatted output to a **string**. The `sprintf()` function takes in two char pointers as input, the first one is the *char-string header addr* of the string to be written, and the second one is the *char-string header addr* of the format string. The `sprintf()` function returns the number of characters written to the string.

The following example shows you how to use `sprintf()` function.
```c
#include <stdio.h>

int main() {
    char str[100];
    int i = 5;
    float f = 5.5;
    char c = 'A';
    char s[] = "Hello";
    sprintf(str, "i = %d, f = %f, c = %c, s = %s", i, f, c, s);
    printf("str: %s\n", str);
    return 0;
}
```

`fprintf(FILE *stream, const char *format, ...)` function in `stdio.h` is used to write formatted output to a **file**. The `fprintf()` function takes in two char pointers as input, the first one is the *FILE* pointer of the file to be written, and the second one is the *char-string header addr* of the format string. The `fprintf()` function returns the number of characters written to the file.

```c
#include <stdio.h>

int main() {
    FILE *fp;
    char str[100];
    int i = 5;
    float f = 5.5;
    char c = 'A';
    char s[] = "Hello";
    fp = fopen("test.txt", "w");
    fprintf(fp, "i = %d, f = %f, c = %c, s = %s", i, f, c, s);
    fclose(fp);
    
    // open the file and print the content
    fp = fopen("test.txt", "r");
    fgets(str, 100, fp);
    printf("str: %s\n", str);
    fclose(fp);

    // remove the file
    remove("test.txt");
    return 0;
}
```

## 3. Message from Error & Signal 
### 3.1 Error Message: strerror()
We can use [`strerror(int errnum)`](https://man7.org/linux/man-pages/man3/strerror.3.html) function to get the error message of the error code from system calls. The `strerror()` function takes in an integer as input of error code, returning a char pointer to the error message.

```c
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // open a file that does not exist
    FILE *fp;
    fp = fopen("test.txt", "r");
    if (fp == NULL) {
        printf("Error: %s\n", strerror(errno));
    }
    return 0;
}
```

### 3.2 Signal Message: strsignal()
We can use [`strsignal(int signum)`](https://man7.org/linux/man-pages/man3/strsignal.3.html) function to get the signal message of the signal code from system calls. The `strsignal()` function takes in an integer as input of signal num and returns a char pointer to the signal message.

```c
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signum) {
    printf("Signal: %s\n", strsignal(signum));
    exit(0);
}

int main() {
    signal(SIGINT, handler);
    while (1) {
        printf("Hello World\n");
        sleep(1);
    }
    return 0;
}
```