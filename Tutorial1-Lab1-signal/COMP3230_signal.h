// file: COMP3230_signal.h
// description: signal names
#ifndef COMP3230_SIGNAL
#define COMP3230_SIGNAL
char *signal_list[] = {
    "NULL", // 0 - NULL, not used
    "SIGHUP", // 1
    "SIGINT", // 2
    "SIGQUIT", // 3
    "SIGILL", // 4
    "SIGTRAP", // 5
    "SIGABRT", // 6
    "SIGBUS", // 7
    "SIGFPE", // 8
    "SIGKILL", // 9
    "SIGUSR1", // 10
    "SIGSEGV", // 11
    "SIGUSR2", // 12
    "SIGPIPE", // 13
    "SIGALRM", // 14
    "SIGTERM", // 15
    "SIGSTKFLT", // 16
    "SIGCHLD", // 17
    "SIGCONT", // 18
    "SIGSTOP", // 19
    "SIGTSTP", // 20
    "SIGTTIN", // 21
    "SIGTTOU", // 22
    "SIGURG", // 23
    "SIGXCPU", // 24
    "SIGXFSZ", // 25
    "SIGVTALRM", // 26
    "SIGPROF", // 27
    "SIGWINCH", // 28
    "SIGIO", // 29
    "SIGPWR", // 30
    "SIGSYS", // 31
};

char *signal_des[] = {
    "NULL", // 0 - NULL, not used
    "hangup", // 1
    "interrupt", // 2
    "quit", // 3
    "illegal instruction", // 4
    "trace trap", // 5
    "abort", // 6
    "bus error", // 7
    "floating point exception", // 8
    "kill", // 9
    "user defined signal 1", // 10
    "segmentation violation", // 11
    "user defined signal 2", // 12
    "broken pipe", // 13
    "alarm clock", // 14
    "software termination signal", // 15
    "stack fault", // 16
    "child status has changed", // 17
    "continue", // 18
    "stop", // 19
    "keyboard stop", // 20
    "background read from tty", // 21
    "background write to tty", // 22
    "urgent condition on socket", // 23
    "cpu time limit exceeded", // 24
    "file size limit exceeded", // 25
    "virtual alarm clock", // 26
    "profiling alarm clock", // 27
    "window size change", // 28
    "I/O now possible", // 29
    "power failure", // 30
    "bad system call", // 31
};
#endif /* COMP3230_SIGNAL */
