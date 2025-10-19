#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <pthread.h>

//example


int a = 0, iret;

void* thr_func(void* arg) {
    for (int i = 0; i < 1000000; i++) { 
        a += 1; 
        //__atomic_fetch_add(&a, 1, __ATOMIC_SEQ_CST);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thr1, thr2;

    iret = pthread_create(&thr1, NULL, thr_func, NULL);
    if (iret != 0) { 
        perror("Cannot Create Thread"); 
    }
    iret = pthread_create(&thr2, NULL, thr_func, NULL);
    if (iret != 0) { 
        perror("Cannot Create Thread"); 
    }

    iret = pthread_join(thr1, NULL);
    if (iret != 0) { 
        perror("Cannot Collect Thread"); 
    }
    iret = pthread_join(thr2, NULL);
    if (iret != 0) { 
        perror("Cannot Collect Thread"); 
    }

    printf("%d", a);
}

// ------------------------------

// Mutex lock

// int a = 0, iret;
// pthread_mutex_t lock;

// void* thr_func(void* arg) {
//     for (int i = 0; i < 1000000; i++) {
//         pthread_mutex_lock(&lock);
//         a++;
//         pthread_mutex_unlock(&lock);
//     }
//     pthread_exit(NULL);
// }

// int main() {
//     pthread_t thr1, thr2;
//     pthread_mutex_init(&lock, NULL); // NULL -> default

//     iret = pthread_create(&thr1, NULL, thr_func, NULL);
//     if (iret != 0) { 
//         perror("Cannot Create Thread"); 
//     }
//     iret = pthread_create(&thr2, NULL, thr_func, NULL);
//     if (iret != 0) { 
//         perror("Cannot Create Thread"); 
//     }

//     iret = pthread_join(thr1, NULL);
//     if (iret != 0) { 
//         perror("Cannot Collect Thread"); 
//     }
//     iret = pthread_join(thr2, NULL);
//     if (iret != 0) { 
//         perror("Cannot Collect Thread"); 
//     }

//     pthread_mutex_destroy(&lock);

//     printf("%d", a);
// }


// Mutex lock - multiple threads

// int a = 0, b = 0, iret;
// pthread_mutex_t lock_a, lock_b;

// void* thr_func(void* arg) {
//     for (int i = 0; i < 1000000; i++) {
//         if (pthread_mutex_trylock(&lock_a) == 0) {
//             a++;
//             pthread_mutex_unlock(&lock_a);
//         } else if (pthread_mutex_trylock(&lock_b) == 0) {
//             b++;
//             pthread_mutex_unlock(&lock_b);
//         }
//     }
//     pthread_exit(NULL);
// }

// int main() {
//     pthread_t thr1, thr2;
//     pthread_mutex_init(&lock_a, NULL);
//     pthread_mutex_init(&lock_b, NULL);
//     iret = pthread_create(&thr1, NULL, thr_func, NULL);
//     if (iret != 0) { 
//         perror("Cannot Create Thread"); 
//     }
//     iret = pthread_create(&thr2, NULL, thr_func, NULL);
//     if (iret != 0) { 
//         perror("Cannot Create Thread"); 
//     }

//     iret = pthread_join(thr1, NULL);
//     if (iret != 0) { 
//         perror("Cannot Collect Thread"); 
//     }
//     iret = pthread_join(thr2, NULL);
//     if (iret != 0) { 
//         perror("Cannot Collect Thread"); 
//     }

//     pthread_mutex_destroy(&lock_a);
//     pthread_mutex_destroy(&lock_b);
//     printf("a = %d, b = %d\n", a, b);
//     printf("a + b = %d\n", a + b);
// }