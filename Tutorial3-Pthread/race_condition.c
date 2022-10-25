#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <pthread.h>



// ============================== 1: Race Condition ====================================

// >>>> 1.1: sharing data across threads of the same process (No race condition) -------

// int x=0;
// void* func(){
//     x++;
// }

// int main(int argc, char* argv[]){
//     pthread_t t1, t2;
//     if (pthread_create(&t1, NULL, &func, NULL) != 0){
//         return 1;
//     }
//     if (pthread_create(&t2, NULL, &func,  NULL) != 0){
//         return 2;
//     }
//     if (pthread_join(t1, NULL) != 0){
//         return 3;
//     }
//     if (pthread_join(t2, NULL) != 0){
//         return 4;
//     }
//     printf("the final result: x=%d\n",x);
//     return 0;
// }

// >>>> 1.2: sharing data across threads of the same process (race condition) -------

int x=0;
void* func(){
    for (int i=0;i<10000000;i++){
        x++;
    }
}

int main(int argc, char* argv[]){
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &func, NULL) != 0){
        return 1;
    }
    if (pthread_create(&t2, NULL, &func,  NULL) != 0){
        return 2;
    }
    if (pthread_join(t1, NULL) != 0){
        return 3;
    }
    if (pthread_join(t2, NULL) != 0){
        return 4;
    }
    printf("the final result: x=%d\n",x);
    return 0;
}
// !!: using ``gcc -S race_condition.c`` to check the assembly code of 'x++', 
// then you will know why dose the race condition happen.




// ============================== 2: Mutex Lock ====================================

// >>>> 2.1: Mutex Lock fixes the race condition -------

// int x=0;
// pthread_mutex_t mutex;

// void* func(){
//     for (int i=0;i<10000000;i++){
//         pthread_mutex_lock(&mutex);
//         x++;
//         pthread_mutex_unlock(&mutex);
//     }
// }

// int main(int argc, char* argv[]){
//     pthread_t t1, t2;
//     pthread_mutex_init(&mutex,NULL);

//     if (pthread_create(&t1, NULL, &func, NULL) != 0){
//         return 1;
//     }
//     if (pthread_create(&t2, NULL, &func,  NULL) != 0){
//         return 2;
//     }
//     if (pthread_join(t1, NULL) != 0){
//         return 3;
//     }
//     if (pthread_join(t2, NULL) != 0){
//         return 4;
//     }
//     pthread_mutex_destroy(&mutex);
//     printf("the final result: x=%d\n",x);
//     return 0;
// }


// >>>> 2.2 Another simpler way to create mutex lock (with 'NULL' attributes) -----------

// int x=0;
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// void* func(){
//     for (int i=0;i<10000000;i++){
//         pthread_mutex_lock(&mutex);
//         x++;
//         pthread_mutex_unlock(&mutex);
//     }
// }

// int main(int argc, char* argv[]){
//     pthread_t t1, t2;
//     // pthread_mutex_init(&mutex,NULL);

//     if (pthread_create(&t1, NULL, &func, NULL) != 0){
//         return 1;
//     }
//     if (pthread_create(&t2, NULL, &func,  NULL) != 0){
//         return 2;
//     }
//     if (pthread_join(t1, NULL) != 0){
//         return 3;
//     }
//     if (pthread_join(t2, NULL) != 0){
//         return 4;
//     }
//     // pthread_mutex_destroy(&mutex);
//     printf("the final result: x=%d\n",x);
//     return 0;
// }




// ============================== 3: Mutex trylock ====================================
// Consider we have two shared variables x and y. 
// And the job of the created threads is to add 1 to x OR y.

// int x=0;
// int y=0;
// pthread_mutex_t mutex_x = PTHREAD_MUTEX_INITIALIZER;
// pthread_mutex_t mutex_y = PTHREAD_MUTEX_INITIALIZER;

// void* func(){
//     for (int i=0;i<1000000;i++){
//         if (pthread_mutex_trylock(&mutex_x) == 0){
//             x++;
//             pthread_mutex_unlock(&mutex_x);
//         }
//         else if (pthread_mutex_trylock(&mutex_y) == 0){
//             y++;
//             pthread_mutex_unlock(&mutex_y);
//         }
//         else {
//             printf("Nothing to do.\n");
//         }
//     }
// }
// int main(int argc, char* argv[]){
//     pthread_t t1, t2;

//     if (pthread_create(&t1, NULL, &func, NULL) != 0){
//         return 1;
//     }
//     if (pthread_create(&t2, NULL, &func,  NULL) != 0){
//         return 2;
//     }
//     if (pthread_join(t1, NULL) != 0){
//         return 3;
//     }
//     if (pthread_join(t2, NULL) != 0){
//         return 4;
//     }
//     printf("the final result: x=%d\n",x);
//     printf("the final result: y=%d\n",y);
//     printf("the final result: x+y=%d\n",x+y);
//     return 0;
// }