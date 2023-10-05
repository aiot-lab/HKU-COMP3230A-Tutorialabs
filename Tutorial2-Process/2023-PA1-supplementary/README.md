# Supplementary material for PA1 (2023)
## 1. Introduction
This repository contains supplementary material for PA1 (2023). The material is organized as follows:
- readproc-example.c: A simple C program that reads the /proc file system.
- waitid-example.c: A simple C program that uses waitid() system call to wait for a child process to terminate and keep the resource usage information.
- exit-status-normal.c : A simple C program that parent process waits for the child process to terminate and check the exit status of the child process.
- - exit-status-signal.c : A simple C program that parent process waits for the child process to terminate with a signal and check the caught signal.

## 2. How to use
Run `make all` to compile all the C programs. The compiled binaries will have the same name as the source file. For example, `readproc-example.c` will be compiled to `readproc-example`. To run the compiled binary, use `./binary-name`. For example, `./readproc-example`.

### 2.1. readproc-example.c
This program shows you how to read the /proc file system. 

The program starts a child process and let it wait for user's 'Enter' key. The parent process reads the /proc file system and prints the information of the child process. While the child process is waiting for user's 'Enter' key, you can open another terminal and run `cat /proc/<PID>/stat` or `cat /proc/<PID>/status` to see the information of the child process.


### 2.2. waitid-example.c
This program shows you how to use waitid() system call to wait for a child process to terminate and keep the resource usage information.

`waitid` has 4 parameters:
- idtype: The type of the ID specified in id. It can be P_PID, P_PGID, or P_ALL.
- id: The ID of the child process to wait for. If idtype is P_PID, id is the process ID of the child process. If idtype is P_PGID, id is the process group ID of the child process. If idtype is P_ALL, id is ignored.
- infop: A pointer to a siginfo_t structure that is used to return information about the child process.
- options: The options for waitid(). It can be WEXITED, WSTOPPED, WCONTINUED, WNOHANG, or WNOWAIT.


WEXITED: The caller is interested in children that have terminated. If this option is not specified, the caller is interested in children that have stopped or continued.
WNOWAIT: Leave the child in a waitable state. A later wait call can be used to again retrieve the child status information. 

With a combination of WEXITED and WNOWAIT (see the example code), the parent process can wait for the child process to terminate and keep the resource usage information (e.g /proc/<PID>/stat and /proc/<PID>/status) for later use.

### 2.3. exit-status-normal.c
This program shows you how to check the exit status of a child process. The exit status of a child process can be checked by using the WIFEXITED and WEXITSTATUS macros.

WIFEXITED: returns true if the child terminated normally.
WEXITSTATUS: returns the exit status of the child.

### 2.4. exit-status-signal.c
This program shows you how to check the exit status of a child process. The exit status of a child process can be checked by using the WIFSIGNALED and WTERMSIG macros.

WIFSIGNALED: returns true if the child terminated because of a signal that was not caught.
WTERMSIG: returns the number of the signal that caused the child to terminate.
