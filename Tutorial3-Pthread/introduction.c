#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <pthread.h> 
#include <sys/syscall.h>


// example
int main() {
    int *a;
    a = malloc(100 * sizeof(int));
    for (int i = 0; i < 100; i++) { 
        a[i] = i; 
    }

    for (int i = 0; i < 100; i++) {
        a[i] = a[i] * 2;
    }
}
// ----------------------------------------


//Define Thread Functions

// int* a;

// void* thr1_func(void* arg) {
//     for (int i = 0; i < 50; i++) { 
//         a[i] = a[i] * 2; 
//     }
// }

// void* thr2_func(void* arg) {
//     for (int i = 50; i < 100; i++) { 
//         a[i] = a[i] * 2; 
//     }
// }

// int main() {
//     a = malloc(100 * sizeof(int));
//     for (int i = 0; i < 100; i++) { 
//         a[i] = i; 
//     }

//     for (int i = 0; i < 100; i++) {
//         a[i] = a[i] * 2;
//     }
// }
// ----------------------------------------


//Create Threads

// int* a;

// void* thr1_func(void* arg) {
//     for (int i = 0; i < 50; i++) { 
//         a[i] = a[i] * 2; 
//     }
// }

// void* thr2_func(void* arg) {
//     for (int i = 50; i < 100; i++) { 
//         a[i] = a[i] * 2; 
//     }
// }

// int main() {
//     a = malloc(100 * sizeof(int));
//     for (int i = 0; i < 100; i++) { 
//         a[i] = i; 
//     }

//     pthread_t thr1, thr2;
//     pthread_attr_t* attr = NULL;
//     int iret;

//     iret = pthread_create(&thr1, attr, thr1_func, NULL);
//     if (iret != 0) { 
//         perror("Cannot Create Thread 1"); 
//     }
//     iret = pthread_create(&thr2, attr, thr2_func, NULL);
//     if (iret != 0) { 
//         perror("Cannot Create Thread 2"); 
//     }

// }
// ----------------------------------------

// Terminate Threads

// int* a;

// void* thr1_func(void* arg) {
//     for (int i = 0; i < 50; i++) { 
//         a[i] = a[i] * 2; 
//     }
//     pthread_exit(NULL);
// }

// void* thr2_func(void* arg) {
//     for (int i = 50; i < 100; i++) { 
//         a[i] = a[i] * 2; 
//     }
//     pthread_exit(NULL);
// }

// int main() {
//     a = malloc(100 * sizeof(int));
//     for (int i = 0; i < 100; i++) { 
//         a[i] = i; 
//     }

//     pthread_t thr1, thr2;
//     pthread_attr_t* attr = NULL;
//     int iret;

//     iret = pthread_create(&thr1, attr, thr1_func, NULL);
//     if (iret != 0) { 
//         perror("Cannot Create Thread 1"); 
//     }
//     iret = pthread_create(&thr2, attr, thr2_func, NULL);
//     if (iret != 0) { 
//         perror("Cannot Create Thread 2"); 
//     }

//     iret = pthread_join(thr1, NULL);
//     if (iret != 0) { 
//         perror("Cannot Collect Thread 1"); 
//     }
//     iret = pthread_join(thr2, NULL);
//     if (iret != 0) { 
//         perror("Cannot Collect Thread 2"); 
//     }
// }
// ----------------------------------------


// Improvement - Accepting Parameters


// int* a;

// void* thr_func(void* arg) {
//     int id = *(int*) arg; // (int*) turn void ptr to int ptr
//     for (int i = 50 * id; i < 50 * (id + 1); i++) { 
//         a[i] = a[i] * 2; 
//     }
//     pthread_exit(NULL);
// }

// int main() {
//     a = malloc(100 * sizeof(int));
//     for (int i = 0; i < 100; i++) { 
//         a[i] = i; 
//     }

//     pthread_t* thrs = malloc(2 * sizeof(pthread_t));
//     pthread_attr_t* attr = NULL;
//     int iret;
//     int* args = malloc(2 * sizeof(int)); 
//     args[0] = 0; 
//     args[1] = 1;

//     for (int i = 0; i < 2; i++) {
//         iret = pthread_create(&thrs[i], attr, thr_func, &args[i]);
//         if (iret != 0) { 
//             perror("Cannot Create Thread %d", i); 
//         }
//     }

//     for (int i = 0; i < 2; i++) {
//         iret = pthread_join(thrs[i], NULL);
//         if (iret != 0) { 
//             perror("Cannot Collect Thread 1"); 
//         }
//     }
// }
// ----------------------------------------

//Improvement - Collecting Return Value


// int* a, *ret_vals;

// void* thr_func(void* arg) {
//     int id = *(int*) arg; // (int*) turn void ptr to int ptr
//     for (int i = 50 * id; i < 50 * (id + 1); i++) { 
//         a[i] = a[i] * 2; 
//     }
//     ret_vals[id] = id;
//     pthread_exit(NULL);
// }

// int main() {
//     a = malloc(100 * sizeof(int));
//     for (int i = 0; i < 100; i++) { 
//         a[i] = i; 
//     }

//     pthread_t* thrs = malloc(2 * sizeof(pthread_t));
//     pthread_attr_t* attr = NULL;
//     int iret;
//     ret_vals = malloc(2 * sizeof(int));
//     int args[] = {0, 1};

//     for (int i = 0; i < 2; i++) {
//         iret = pthread_create(&thrs[i], attr, thr_func, &args[i]);
//         if (iret != 0) { 
//             perror("Cannot Create Thread"); 
//         }
//     }

//     for (int i = 0; i < 2; i++) {
//         iret = pthread_join(thrs[i], NULL);
//         if (iret != 0) { 
//             perror("Cannot Collect Thread"); 
//         }
//         printf("Thread %d returns %d\n", i, ret_vals[i]);
//     }
// }

// ----------------------------------------

//Identification

// void* thr_func(void* arg) {
//     int i = *(int*) arg; // (int*) turn void ptr to int ptr
//     printf("Thread %d: \nMy pthread id is %ld \nMy process id is %d\nMy system id is %ld\n", 
//         i, pthread_self(), getpid(), syscall(SYS_gettid));
//     pthread_exit(NULL);
// }

// int main() {
//     pthread_t* thrs = malloc(2 * sizeof(pthread_t));
//     pthread_attr_t* attr = NULL;
//     int iret, args[] = {0, 1};

//     printf("Main Thread Process id %d\n", getpid());

//     for (int i = 0; i < 2; i++) {
//         iret = pthread_create(&thrs[i], attr, thr_func, &args[i]);
//         printf("Main Thread: \nCreate Thread %d with pthread_id %ld\n", i, thrs[i]);
//     }

//     for (int i = 0; i < 2; i++) {
//         iret = pthread_join(thrs[i], NULL);
//         if (iret != 0) perror("Cannot Collect Thread");
//     }
// }

// ----------------------------------------

//Cancellation

// void* thr1_func(void* arg) {
//     printf("func1 disable cancellation\n");
//     pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
//     sleep(5);
//     printf("func1 enable cancellation\n");
//     pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
//     pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
//     while (1) {
//         printf("...");
//     }
//     // NO EXIT
// }

// void* thr2_func(void* arg) {
//     pthread_t tid = *(pthread_t*)arg;
//     for (int i = 0; i < 4; i++) {
//         printf("func2 sends a cancellation request to func1\n");
//         pthread_cancel(tid);
//         sleep(2);
//     }
//     pthread_exit(NULL);
// }

// int main() {
//     pthread_t thread_id1, thread_id2;

//     pthread_create(&thread_id1, NULL, thr1_func, NULL);
//     sleep(2);
//     pthread_create(&thread_id2, NULL, thr2_func, (void*)&thread_id1);

//     pthread_join(thread_id1, NULL);
//     printf("func1 has terminated\n");
//     pthread_join(thread_id2, NULL);
//     printf("func2 has terminated\n");
//     return 0;
// }
// ----------------------------------------
