#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <pthread.h> 
#include <sys/syscall.h>


void* func1(void* arg){
    int* a = (int*) arg;
    for (int i =1; i<1000000; i++){
        (*a)++;
    }
    return 0;
}


void* func2(void* arg){
    int* b = (int*) arg;
    for (int i =1; i<1000000; i++){
        (*b)--;
    }
    return 0;
}

int main(int argc, char * argv[]){
    int a = 1;
    int b = 1000000;
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, &func1,(void*) &a);
    pthread_create(&thread2, NULL, &func2, (void*) &b);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    return 0;
}