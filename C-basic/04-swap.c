#include <stdio.h>

void swap0(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void swap1(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap2(int *a, int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

int main(int argc, char *argv[]) {
    int a = 1, b = 2;
    printf("ori-> a = %d, b = %d\n", a, b);
    swap0(a, b);
    printf("swap0: a = %d, b = %d\n", a, b);
    swap1(&a, &b);
    printf("swap1: a = %d, b = %d\n", a, b);
    swap2(&a, &b);
    printf("swap2: a = %d, b = %d\n", a, b);
    return 0;
}