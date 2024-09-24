# T2 - supplement material
This tutorial is designed to help you get a better understanding of Process and make Programming Assignment 1 more managable. This doc is a supplement to T2-slides. 

The key points of this documents are:
1. useful syscalls(**wait4**)
2. Debugging commmands(**follow-fork-mode**, **detach-on-fork**)
3. signals (SIGINT, **SIGCHLD**, **SIGUSR1**, SIGPIPE)


## 1. Useful syscalls
### 1.a exec() family
The exec() family of functions replaces the current process image with a new process image. The new process image is constructed from a regular, executable file called the new process image file. The exec() family of functions includes the following functions (use `ls -l` as example):
1. execvp(): `execvp("ls", ["ls", "-l"])`
2. execlp(): `execlp("ls", "ls", "-l", NULL)`
3. execv(): `execv("/bin/ls", ["ls", "-l"])`
4. execl(): `execl("/bin/ls", "ls", "-l", NULL)`
5. execle(): `execle("/bin/ls", "ls", "-l", NULL, envp)`
6. execve(): `execve("/bin/ls", ["ls", "-l"], envp)`
7. execvpe(): `execvpe("ls", ["ls", "-l"], envp)`

An example is shown in [fork-exec-wait-example4.c](fork-exec-wait-example4.c). 

### 1.b wait() family
The wait() family of functions suspends execution of the calling process until one of its children terminates. The wait() family of functions includes the following functions:

1. wait(int *wstatus):
2. waitpid(pid_t pid, int *wstatus, int options):
3. waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options):

also, there are 2 non-standard functions:
1. wait3(int *wstatus, int options, struct rusage *rusage): wait for any child process
2. **wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage)**: wait for a specific child process

Apart from additional "rusage" option, wait3 and wait4 are identical to waitpid(-1, wstatus, options) and waitpid(pid, wstatus, options, rusage).

#### 1.b.1 wait4()
As `wait3()` is built on top of `wait4()`, the following example will only focus on `wait4()`. By using `wait4()`, you can get more information about the child process, like the resource usage (from parameter rusage). 

See [getrusage(2)](https://man7.org/linux/man-pages/man2/getrusage.2.html) for more information in parameter rusage.

```c
        struct rusage {
               struct timeval ru_utime; /* user CPU time used */
               struct timeval ru_stime; /* system CPU time used */
               long   ru_maxrss;        /* maximum resident set size */
               long   ru_ixrss;         /* integral shared memory size */
               long   ru_idrss;         /* integral unshared data size */
               long   ru_isrss;         /* integral unshared stack size */
               long   ru_minflt;        /* page reclaims (soft page faults) */
               long   ru_majflt;        /* page faults (hard page faults) */
               long   ru_nswap;         /* swaps */
               long   ru_inblock;       /* block input operations */
               long   ru_oublock;       /* block output operations */
               long   ru_msgsnd;        /* IPC messages sent */
               long   ru_msgrcv;        /* IPC messages received */
               long   ru_nsignals;      /* signals received */
               long   ru_nvcsw;         /* voluntary context switches */
               long   ru_nivcsw;        /* involuntary context switches */
           };
```

See [Tutorial2-Process/fork-exec-wait4-example.c](fork-exec-wait4-example.c) for an example of using wait4() to get user/sys time usage.


## 2. multi-process(fork) degbugging using
This section shows you how to debug a multi-process program using `gdb`. Pay attention to follow-fork-mode and detach-on-fork setting in gdb (Step 4).

1. compile with `-g` flag
2. GDB start: run `gdb <program>` to start debugging
3. Breakpoint add: set breakpoint: `b <line number>` or `b <function name>`
4. **GDB settings for fork debug**: useful setting to help debugging fork, enter it in gdb commandline before running:
    * `set follow-fork-mode <child|parent>`, if you want to follow the child process after `fork()`, set it to `child`.
    * `set detach-on-fork <on|off>`, if you want to detach the other process (depending on follow-fork-mode) after `fork()`, set it to `on`.
    * By default `follow-fork-mode = parent` and `detach-on-fork = on` are the default settings. Therefore, if fork() is called, the parent process will be attacted by gdb and the child process will run concurrently to its end.
5. GDB run: run `r` to run the program
6. next line: run `n` to go to the next line
7. step into: run `s` to step into the function
8. step out: run `finish` to step out of the function
9. print variable: run `p <variable name>` to print the value of the variable
10. continue: run `c` to continue the program
11. GDB quit: run `q` to quit the program
12. GDB help: run `h` to get help
13. GDB list: run `l` to list the source code
14. GDB backtrace: run `bt` to get the backtrace of the program


## 3. Signals
Signals used on workbench2 (Ubuntu with Kernel 5.4.0-124-generic) are listed in the following table. Signals may be different on different machines and OSs.

> You can find this information at `/usr/include/x86_64-linux-gnu/bits/signum-generic.h` and `/usr/include/x86_64-linux-gnu/sys/signal.h`.

See also [COMP3230_signal.h](../Tutorial1-Lab1-signal/COMP3230_signal.h) for the signal names and functionality on workbench2.

| No | Signal | Description |
|:--:|:------:|:-----------:|
| 1 | SIGHUP | Hangup detected on controlling terminal or death of controlling process |
| 2 | **SIGINT** | Interrupt from keyboard |
| 3 | SIGQUIT | Quit from keyboard |
| 4 | SIGILL | Illegal Instruction |
| 5 | SIGTRAP | Trace/breakpoint trap |
| 6 | SIGABRT | Abort signal from abort(3) |
| 7 | SIGBUS | BUS error (bad memory access) |
| 8 | SIGFPE | Floating point exception |
| 9 | SIGKILL | Kill signal |
| 10 | **SIGUSR1** | User-defined signal 1 |
| 11 | SIGSEGV | Invalid memory reference |
| 12 | SIGUSR2 | User-defined signal 2 |
| 13 | **SIGPIPE** | Broken pipe: write to pipe with no readers |
| 14 | SIGALRM | Timer signal from alarm(2) |
| 15 | SIGTERM | Termination signal |
| 16 | SIGSTKFLT | Stack fault on coprocessor |
| 17 | **SIGCHLD** | Child stopped or terminated |
| 18 | SIGCONT | Continue if stopped |
| 19 | SIGSTOP | Stop process |
| 20 | SIGTSTP | Stop typed at tty |
| 21 | SIGTTIN | tty input for background process |
| 22 | SIGTTOU | tty output for background process |
| 23 | SIGURG | Urgent condition on socket |
| 24 | SIGXCPU | CPU time limit exceeded (see setrlimit(2)) |
| 25 | SIGXFSZ | File size limit exceeded (see setrlimit(2)) |
| 26 | SIGVTALRM | Virtual alarm clock (see setitimer(2)) |
| 27 | SIGPROF | Profiling alarm clock (see setitimer(2)) |
| 28 | SIGWINCH | Window size change (see ioctl(2)) |
| 29 | SIGIO | I/O now possible (see fcntl(2)) |
| 30 | SIGPWR | Power failure restart |
| 31 | SIGSYS | Bad system call |

### 3.a SIGINT: handle a sys-defined signal
Please refer to [Tutorial1-Lab1-signal/02_signal_int_handle.c](../Tutorial1-Lab1-signal/02_signal_int_handle.c)

### 3.b SIGUSR1: send&handle a user-defined signal
This section is to show you how to send a signal and handle it (use SIGUSR1 as an example).

#### 3.b.1 raise a signal
1. `raise(SIGUSR1)`: raise a signal in the current process. see [Tutorial1-Lab1-signal/08_signal_fpe_raise_handle.c`](../Tutorial1-Lab1-signal/08_signal_fpe_raise_handle.c)
2. `kill(pid, SIGUSR1)`: send a signal to a process `pid`. Similar to `raise`, but you can specify the process who receives the signal.

#### 3.b.2 handle a signal
1. use `signal(SIGUSR1, handler)`: set the handler for the signal `SIGUSR1`. 
2. use `sigaction(SIGUSR1, &act, NULL)`: set the handler for the signal `SIGUSR1`. The difference between `signal` and `sigaction` is that `sigaction` allows you to set more options and get more information about the signal. See [signal(7)](https://man7.org/linux/man-pages/man7/signal.7.html)

The following example shows you how to define a signal handler using sigaction to get the sender of the signal.

```c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// use sigaction to handle SIGUSR1
void handler(int sig, siginfo_t *info, void *ucontext) {
    printf("receive signal %d from %d\n", sig, info->si_pid);
}
int main() {
    // sigaction
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO; // set the flag to allow the handler to receive more information, like
    sigaction(SIGUSR1, &act, NULL);

    // signal
    // signal(SIGUSR1, handler);

    while (1) {
        printf("I'm process %d, waiting SIGUSR1.\n", getpid());
        sleep(1);
    }
    return 0;
}
```

### 3.c SIGCHLD: handle the signal when a child process terminates
SIGCHLD is sent to the parent process when a child process terminates. The parent process can use this signal to know the status of the child process. The following example shows you how to use SIGCHLD to get the status of the child process.

See [Tutorial1-Lab1-signal/17_signal_chld_handle.c](../Tutorial1-Lab1-signal/17_signal_chld_handle.c)

### 3.d SIGPIPE: handle the signal when a pipe is broken
SIGPIPE is sent to the process when a pipe is broken. The following example shows you when SIGPIPE is sent.

See [lab2-pipesig.c](lab2-pipesig.c)
