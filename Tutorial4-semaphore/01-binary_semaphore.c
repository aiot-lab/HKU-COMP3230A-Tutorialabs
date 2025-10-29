#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TOTAL_COUNT 10000

sem_t sem01;

int count = 0;

void *increaseWithoutSemaphore(void *arg) {
  int i;
  for (i = 0; i < TOTAL_COUNT; i++) {
    count++;
    if ((count % 5000) == 0) { // print progress every 5000 times
      int id = *((int *)arg);
      printf("%s Thread %d: count = %d\n", __func__, id, count);
    }
  }
  pthread_exit(0);
}

void *increaseWithSemaphore(void *arg) {
  int i;
  for (i = 0; i < TOTAL_COUNT; i++) {
    sem_wait(&sem01);
    count++;
    if ((count % 5000) == 0) {
      int id = *((int *)arg);
      printf("%s Thread %d: count = %d\n", __func__, id, count);
    }
    sem_post(&sem01);
  }
  pthread_exit(0);
}

void checkCount(int numThreads){
  if (count != numThreads * TOTAL_COUNT)
    printf("Error! current count is %d. total count should be %d\n\n", count, numThreads * TOTAL_COUNT);
  else
    printf("OK. current count is %d\n\n", count);
}

int main() {
  sem_init(&sem01, 0, 1);
  int numThreads = 4;
  pthread_t threads[numThreads];
  int tids[numThreads];

  for (int i = 0; i < numThreads; ++i) {
    tids[i] = i;
    if (pthread_create(&threads[i], NULL, &increaseWithoutSemaphore, (void *)&tids[i])) {
      printf("ERROR creating thread 1\n");
      exit(1);
    } 
  } 
  for (int i = 0; i < numThreads; ++i) {
    pthread_join(threads[i], NULL);
  } 
  checkCount(numThreads);

  count = 0;
  for (int i = 0; i < numThreads; ++i) {
    tids[i] = i;
    if (pthread_create(&threads[i], NULL, &increaseWithSemaphore, (void *)&tids[i])) {
      printf("ERROR creating thread 1\n");
      exit(1);
    } 
  } 
  for (int i = 0; i < numThreads; ++i) {
    pthread_join(threads[i], NULL);
  } 
  checkCount(numThreads);

  sem_destroy(&sem01);
  return 0;
}
