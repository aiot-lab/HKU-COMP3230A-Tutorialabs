// file: singal_sync_div0.c
// description: signal handler example for FPE signal.
// #define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "COMP3230_signal.h"

int main(int argc, char *argv[]) {
    int a = 0;
    int b = 1;
    int c = b / a;
    return 0;
}
