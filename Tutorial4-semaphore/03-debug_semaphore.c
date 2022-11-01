#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

// macros to check return values of pthread functions
#define CHECK_ERR(a,msg) \
    do {if ((a)) {\
            fprintf(stderr, "Error %s: %d\\n", msg, a);\
            exit(EXIT_FAILURE);\
        }\
    } while(0)

// Static variable:
// static int shared_var = 0;
static sem_t order;

void *run_A(void *p)
{
    sem_post(&order);
    printf("A"); fflush(stdout);
    pthread_exit(NULL);
}

void *run_B(void *p)
{
    sem_wait(&order);
    printf("B"); fflush(stdout);
    pthread_exit(NULL);
}

int main(void){
    int err;
    pthread_t thread_A, thread_B;
    // Create semaphore:
    CHECK_ERR(sem_init(&order, 0, 0), "sem_init");
    // Create threads:
    CHECK_ERR(pthread_create(&thread_A, NULL, run_A, NULL), "pthread_create: A");
    CHECK_ERR(pthread_create(&thread_B, NULL, run_B, NULL), "pthread_create: B");
    // Wait for threads to finish:
    CHECK_ERR(pthread_join(thread_A, NULL), "pthread_join: A");
    CHECK_ERR(pthread_join(thread_B, NULL), "pthread_join: B");
    printf("\n"); fflush(stdout);
    CHECK_ERR(sem_destroy(&order), "sem_destroy");
    return 0;
}