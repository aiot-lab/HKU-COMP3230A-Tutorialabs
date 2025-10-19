#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int* a, *state;
pthread_mutex_t lock; // not race, just for cond
pthread_cond_t cond;

void* thr_func(void* arg) {
    int id = *(int*) arg; // (int*) turn void ptr to int ptr
    for (int i = 50 * id; i < 50 * (id + 1); i++) {
        a[i] = a[i] * 2;
    }
    pthread_mutex_lock(&lock);
    state[id] = 1;
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&cond);
    // can do more here
    sleep(3);
    pthread_exit(NULL);
}

int main() {
    a = malloc(100 * sizeof(int));
    for (int i = 0; i < 100; i++) {
        a[i] = i;
    }

    pthread_mutex_init(&lock, NULL); // NULL -> default
    pthread_cond_init(&cond, NULL);  // NULL -> default

    pthread_t* thrs = malloc(2 * sizeof(pthread_t));
    pthread_attr_t* attr = NULL;
    int iret, args[] = {0, 1};
    state = malloc(2 * sizeof(int)); 
    state[0] = 0; 
    state[1] = 0;

    for (int i = 0; i < 2; i++) {
        iret = pthread_create(&thrs[i], attr, thr_func, &args[i]);
    }

    pthread_mutex_lock(&lock);
    while (state[0] == 0 || state[1] == 0) {
        pthread_cond_wait(&cond, &lock);
    }
    printf("All threads have done their job and still alive\n"); fflush(stdout);
    sleep(3);

    for (int i = 0; i < 2; i++) {
        iret = pthread_join(thrs[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
}
