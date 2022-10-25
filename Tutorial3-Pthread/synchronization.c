#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <pthread.h>


// ============================== 1: Condition Variable ====================================

// >>>> 1.1 -----------------------------

// Consider a variable <octopus> to keep track of your Octopus card balance. 
// If the balance is bigger than 0, you can take the MTR  which cost $10. 
// Otherwise, you need to top up the card for $40, first.

int octopus = 10;
pthread_mutex_t octopus_lock;
pthread_cond_t octopus_cond;

void* cost(){
    for (int i=0; i< 20; i++){
        pthread_mutex_lock(&octopus_lock);
        while(octopus<0){                                       // Is that okay to use 'if' not 'while'?
            printf("Need to top up! octopus = %d \n", octopus);
            pthread_cond_wait(&octopus_cond, &octopus_lock);
        }
        octopus -= 10;
        printf("Take MTR, octopus = %d \n", octopus);
        pthread_mutex_unlock(&octopus_lock);
    }
    return 0;
}

void* topup(){
    for (int i=0; i<10; i++){
        pthread_mutex_lock(&octopus_lock);
        if (octopus >= 0){
            pthread_mutex_unlock(&octopus_lock);
        }
        else{
            octopus += 40;
            printf("Top up octopus. octopus = %d \n", octopus);
            pthread_mutex_unlock(&octopus_lock);
            pthread_cond_signal(&octopus_cond);
            sleep(1);
        }
    }
    return 0;
}

int main(int argc, char* argv[]){
    pthread_mutex_init(&octopus_lock, NULL);
    pthread_cond_init(&octopus_cond, NULL);

    pthread_t consumer, toup_machine;
    pthread_create(&consumer, NULL, &cost, NULL);
    pthread_create(&toup_machine, NULL, &topup, NULL);

    pthread_join(consumer, NULL);
    pthread_join(toup_machine, NULL);

    pthread_mutex_destroy(&octopus_lock);
    pthread_cond_destroy(&octopus_cond);
    return 0;
}


// >>>> 1.2 An simpler version is: -----------------------------
// int octopus = 10;
// pthread_mutex_t octopus_lock = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t octopus_cond = PTHREAD_COND_INITIALIZER;
// pthread_mutex_t octopus_lock;
// pthread_cond_t octopus_cond;

// void* cost(){
//     for (int i=0; i< 20; i++){
//         pthread_mutex_lock(&octopus_lock);
//         while(octopus<0){
//             printf("Need to top up! octopus = %d \n", octopus);
//             pthread_cond_wait(&octopus_cond, &octopus_lock);
//         }
//         octopus -= 10;
//         printf("Take MTR, octopus = %d \n", octopus);
//         pthread_mutex_unlock(&octopus_lock);
//     }
// }

// void* topup(){
//     for (int i=0; i<10; i++){
//         pthread_mutex_lock(&octopus_lock);
//         if (octopus >= 0){
//             pthread_mutex_unlock(&octopus_lock);
//         }
//         else{
//             octopus += 40;
//             printf("Top up octopus. octopus = %d \n", octopus);
//             pthread_mutex_unlock(&octopus_lock);
//             pthread_cond_signal(&octopus_cond);
//             sleep(1);
//         }
//     }
// }

// int main(int argc, char* argv[]){
//     // pthread_mutex_init(&octopus_lock, NULL);
//     // pthread_cond_init(&octopus_cond, NULL);

//     pthread_t consumer, toup_machine;
//     pthread_create(&consumer, NULL, &cost, NULL);
//     pthread_create(&toup_machine, NULL, &topup, NULL);

//     pthread_join(consumer, NULL);
//     pthread_join(toup_machine, NULL);
//     // pthread_mutex_destroy(&octopus_lock);
//     // pthread_cond_destroy(&octopus_cond);
//     return 0;
// }


// >>>> 1.3 What will happen if there are five people use the same octopus: ------------------
// int octopus = 10;
// pthread_mutex_t octopus_lock = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t octopus_cond = PTHREAD_COND_INITIALIZER;

// void* cost(){
//     pthread_t myself = pthread_self(); 
//     for (int i=0; i< 5; i++){
//         pthread_mutex_lock(&octopus_lock);
//         while(octopus<0){
//             printf("%lu: Need to top up! octopus = %d \n",myself, octopus);
//             pthread_cond_wait(&octopus_cond, &octopus_lock);
//         }
//         octopus -= 10;
//         printf("%lu: Take MTR, octopus = %d \n",myself, octopus);
//         pthread_mutex_unlock(&octopus_lock);
//     }
// }

// void* topup(){
//     for (int i=0; i<10; i++){
//         pthread_mutex_lock(&octopus_lock);
//         if (octopus >= 0){
//             pthread_mutex_unlock(&octopus_lock);
//         }
//         else{
//             octopus += 40;
//             printf("Top up octopus. octopus = %d \n", octopus);
//             pthread_mutex_unlock(&octopus_lock);
//             pthread_cond_signal(&octopus_cond);
//             sleep(1);
//         }
//     }
// }

// int main(int argc, char * argv[]){
//     pthread_t consumer[5], toup_machine;
//     for (int i=0; i<5; i++){
//         pthread_create(&consumer[i], NULL, &cost, NULL);
//     }
//     pthread_create(&toup_machine, NULL, &topup, NULL);
//     for (int i=0; i<5; i++){
//         pthread_join(consumer[i], NULL);
//     }
//     pthread_join(toup_machine, NULL);
//     return 0;
// }

// Each time the machine tops up an Octopus Card, only one waiting consumer will be notified.


// >>>> 1.4 If we want to inform all the waiting consumer, we need pthread_cond_broadcast().-----------
// int octopus = 10;
// pthread_mutex_t octopus_lock = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t octopus_cond = PTHREAD_COND_INITIALIZER;

// void* cost(){
//     for (int i=0; i< 5; i++){
//         pthread_t myself = pthread_self(); 
//         pthread_mutex_lock(&octopus_lock);
//         while(octopus<0){
//             printf("%lu: Need to top up! octopus = %d \n",myself, octopus);
//             pthread_cond_wait(&octopus_cond, &octopus_lock);
//         }
//         octopus -= 10;
//         printf("%lu: Take MTR, octopus = %d \n",myself, octopus);
//         pthread_mutex_unlock(&octopus_lock);
//     }
// }

// void* topup(){
//     for (int i=0; i<10; i++){
//         pthread_mutex_lock(&octopus_lock);
//         if (octopus >= 0){
//             pthread_mutex_unlock(&octopus_lock);
//         }
//         else{
//             octopus += 40;
//             printf("Top up octopus. octopus = %d \n", octopus);
//             pthread_mutex_unlock(&octopus_lock);
//             pthread_cond_broadcast(&octopus_cond);
//             sleep(1);
//         }
//     }
// }

// int main(int argc, char * argv[]){
//     pthread_t consumer[5], toup_machine;
//     for (int i=0; i<5; i++){
//         pthread_create(&consumer[i], NULL, &cost, NULL);
//     }
//     pthread_create(&toup_machine, NULL, &topup, NULL);

//     for (int i=0; i<5; i++){
//         pthread_join(consumer[i], NULL);
//     }
//     pthread_join(toup_machine, NULL);
//     return 0;
// }




// ============================== 2: Pthread Cancellation ====================================

// >>>> 2.1: How to enable one thread to terminate another thread?--------------------------
// void *func1 (void *arg){
//     printf("func1 set the cancellation state to ignore\n");  
//     pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);  
//     sleep(8);
//     printf("func1 set the cancellation state to enable with immediate action\n"); 
//     sleep(1); 
//     pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);  
//     pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
//     while (1) printf("\n");
// }

// void *func2 (void *arg){
//     int i;
//     pthread_t tid = *(pthread_t *)arg;  
//     for (i=0; i<5; i++) {
//         printf("func2 sends a cancellation request to func1\n");  
//         pthread_cancel(tid);
//         sleep(2);
//     }
//     pthread_exit(NULL);
// }

// int main() {
//     pthread_t thread_id1, thread_id2;
//     pthread_create(&thread_id1, NULL, func1, NULL);  
//     sleep(2);
//     pthread_create(&thread_id2, NULL, func2,(void*)&thread_id1);
//     pthread_join(thread_id1, NULL);
//     printf("func1 has joined the master thread\n");  
//     pthread_join(thread_id2, NULL);
//     printf("func2 has joined the master thread\n");
//     return 0;
// }




// ============================== 3: Pthread Barrier ====================================

// >>>> 3.1: (Example) How to make sure all the created threads start running at the same time if the hardware can support it?
// void* func(){
//     pthread_t myself = pthread_self(); 
//     printf("Running, the pthread_t of myself is: %lu \n", myself);
// }
// int main(int argc, char * argv[]){
//     pthread_t th[5];
//     for (int i=0; i<5; i++){
//         pthread_create(th+i, NULL, &func, NULL);
//         printf("the %d-th thread created\n", i);
//         sleep(1);
//     }
//     for (int i=0; i<5; i++){
//         pthread_join(th[i],NULL);
//     }
//     return 0;
// }


// >>>> 3.2: (Solution) Using pthread barrier ----------------------------------
// pthread_barrier_t barrier;
// void* func(){
//     pthread_barrier_wait(&barrier);
//     pthread_t myself = pthread_self(); 
//     printf("Running, the pthread_t of myself is: %lu \n", myself);
// }
// int main(int argc, char * argv[]){
//     pthread_t th[5];
//     pthread_barrier_init(&barrier,NULL,5);
//     for (int i=0; i<5; i++){
//         pthread_create(th+i, NULL, &func, NULL);
//         printf("the %d-th thread created\n", i);
//         sleep(1);
//     }
//     for (int i=0; i<5; i++){
//         pthread_join(th[i],NULL);
//     }
//     pthread_barrier_destroy(&barrier);
//     return 0;
// }
