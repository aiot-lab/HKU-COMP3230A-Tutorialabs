// file: signal_list.c
// description: print signal list
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "COMP3230_signal.h"

void list_all_signals() {
    int i;
    for (i = 1; i < 32; i++) {
        printf("%s\t %s\n", signal_list[i], signal_des[i]);
    }
}

int main(int argc, char *argv[]) {
    list_all_signals();
    return 0;
}
