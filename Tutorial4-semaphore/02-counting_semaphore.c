#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static sem_t knife_sem;
static sem_t fork_sem;

void *eat(void *arg) {
  int tid = *(int *)arg;
  printf("\tPhilosopher(%d) is hungry!\n", tid);
  int isFull = 0;
  while (!isFull) {
    if(sem_trywait(&knife_sem) == 0){
      printf("Philosopher(%d) picks up a knife\n", tid);
      if(sem_trywait(&fork_sem) == 0){
        printf("Philosopher(%d) picks up a fork\n", tid);
        printf("\tPhilosopher(%d): eating... \n", tid);
        fflush(stdout);
        sleep(1); // takes a second to eat
        isFull = 1;
        printf("\tPhilosopher(%d): Yummy yummy!\n", tid);
        sem_post(&fork_sem);
        printf("Philosopher(%d) puts down the fork\n", tid);
      }
      sem_post(&knife_sem);
      printf("Philosopher(%d) puts down the knife\n", tid);
      fflush(stdout); 
    }
  }
  pthread_exit(0); 
}

int main() {
  int NUM_KNIVES = 4;
  int NUM_FORKS = 3;
  int NUM_PEOPLE = 10;

  sem_init(&knife_sem, 0, NUM_KNIVES);
  sem_init(&fork_sem, 0, NUM_FORKS);
  pthread_t threads[NUM_PEOPLE];
  int tids[NUM_PEOPLE];
  int i, rc;
  for (i = 0; i < NUM_PEOPLE; i++) {
    tids[i] = i;
    if ((rc = pthread_create(&threads[i], NULL, eat, &tids[i]))) {
      fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
      return EXIT_FAILURE;
    }
  }

  for (i = 0; i < NUM_PEOPLE; i++) {
    pthread_join(threads[i], NULL);
  }
  sem_destroy(&knife_sem);
  sem_destroy(&fork_sem);

  return 0;
}
