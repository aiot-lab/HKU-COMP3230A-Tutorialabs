# Tutorialab-Lab1-signal
## To compile the code
```bash
make all
```
## files
1. COMP3230_signal.h: header file, containing the signals name and functionality on the system(workbench2)

2. `<sig_no>_signal_<sig_name>_(<suffix>)_<handle_or_defalt>.c`: 

`<sig_no>`: signal number
`<sig_name>`: signal name
`<suffix>`: suffix: optional, how to trigger the signal(div0/raise)
`<handle_or_defalt>`: define a new routine or use default handler

3. ref-<filename>: reference code of <filename> in C library included

hints to find them: `gcc -H <filename_to_compile>`

4. signal_list.c : list all the signals on the system

## Signal-lab Answer
Q1. Why it fails to override signal handler for SIGFPE? <\br>
A1. Although the signal handler for SIGFPE is overridden and execution of the signal handler is successful, the main program is still in a dead loop of "SIGFPE->handle->SIGFPE". One possible solution is to restore the environment of the main program before the possible SIGFPE occurs.
```c
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

jmp_buf env;

void sigfpe_handler(int signo)
{
    printf("SIGFPE caught!\n");
    longjmp(env, 1);
}

int main()
{
    signal(SIGFPE, sigfpe_handler);
    if (setjmp(env) == 0) {
        int a = 1;
        int b = 0;
        int c = a / b;
    } else {
        printf("SIGFPE handled!\n");
    }
    return 0;
}
```
