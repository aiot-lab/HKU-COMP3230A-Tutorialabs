// file: heap_addr.c
// description: print heap address
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("code address: %p", main);

    int *p = (int *)malloc(sizeof(int));
    printf("heap address: %p\n", p);
    
    int x = 0;
    printf("stack address: %p\n", &x);
    return 0;
}