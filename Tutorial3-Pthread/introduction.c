#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <pthread.h> 
#include <sys/syscall.h>

// ============================== 1: Creating thread ====================================

// >>>> 1.1: creating a thread. -----------------------------------

// void* func(){
//     printf("Test the pthread\n");
// }

// int main(int argc, char * argv[]){
//     pthread_t thread1;
//     pthread_create(&thread1, NULL, &func, NULL);
//     pthread_join(thread1,NULL);
//     return 0;
// }

// >>>> 1.2: (Coding Safety) creating a thread. -----------------------------------

// void* func(){
//     printf("Test the pthread\n");
// }

// int main(int argc, char * argv[]){
//     pthread_t thread1;
//     if (pthread_create(&thread1, NULL, &func, NULL) != 0){
//         return 1;
//     }
//     if (pthread_join(thread1,NULL) != 0){
//         return 2;
//     }
//     return 0;
// }

// >>>> 1.3: creating multiple threads with loop. ---------------------

// 1.3.1: creating multiple threads with loop. (Wrong implementation)

// void* func(){
//     printf("Test the pthread\n");
// }

// int main(int argc, char * argv[]){
//     pthread_t th[10];
//     for (int i=0; i<10; i++){
//         pthread_create(th+i, NULL, &func, NULL);
//         printf("the %d-th thread created\n", i);
//         pthread_join(th[i],NULL);
//         printf("the %d-th thread terminated\n", i);
//     }
//     return 0;
// }
// In this case, the threads do not parallelly execute.

// 1.3.2: creating multiple threads with loop. (Right implementation)

// void* func(){
//     printf("Test the pthread\n");
// }
// int main(int argc, char * argv[]){
//     pthread_t th[10];
//     for (int i=0; i<10; i++){
//         pthread_create(th+i, NULL, &func, NULL);
//         printf("the %d-th thread created\n", i);
//     }

//     for (int i=0; i<10; i++){
//         pthread_join(th[i],NULL);
//         printf("the %d-th thread terminated\n", i);
//     }
//     return 0;
// }
// In this case, the threads are parallelly executed. However, 
// the output order of "thread termination" is not the real order of threads' terminations.
// Question: How to determine the first terminated thread?





// ============================== 2: pthread_t in the code ====================================

// >>>> 2.1: what is the pthread_t in the code? -----------------------------------

// void* func(){
//     printf("Test the pthread\n");
// }

// int main(int argc, char * argv[]){
//     pthread_t thread1;
//     if (pthread_create(&thread1, NULL, &func, NULL) != 0){
//         return 1;
//     }
//     printf("the created thread1 is: %lu\n",thread1);  
//     // the value of thread1 is a long unsigned int.
//     if (pthread_join(thread1,NULL) != 0){
//         return 2;
//     }
//     return 0;
// }

// >>>> 2.2: How to get the pthread_t by the thread itself? ----------------------------

// void* func(){
//     pthread_t myself = pthread_self();  // Similar with the getpid() in process
//     printf("the pthread_t of myself is: %lu \n", myself);
// }

// int main(int argc, char * argv[]){
//     pthread_t thread1;
//     if (pthread_create(&thread1, NULL, &func, NULL) != 0){
//         return 1;
//     }
//     printf("the created thread1 is: %lu\n",thread1);  
//     // the value of thread1 is a long unsigned int.
//     if (pthread_join(thread1,NULL) != 0){
//         return 2;
//     }
//     return 0;
// }
// The pthread_t is the id of the thread that is used by the pthread library. 
// Question: What is the id of the thread in the OS?

// >>>> 2.3: How to get the thread's ID in OS -----------------------------------

// void* func(){
//     pthread_t myself = pthread_self();  // Similar with the getpid() in process
//     printf("the pthread_t of myself is: %lu \n", myself);

//     pid_t thread_id;
//     thread_id = syscall(SYS_gettid);
//     printf("the thread ID in OS is: %d \n", thread_id);
// }
// int main(int argc, char * argv[]){
//     pthread_t thread1;
//     if (pthread_create(&thread1, NULL, &func, NULL) != 0){
//         return 1;
//     }
//     printf("the created thread1 is: %lu\n",thread1);  
//     // the value of thread1 is a long unsigned int.
//     if (pthread_join(thread1,NULL) != 0){
//         return 2;
//     }
//     return 0;
// }





// ============================== 3: pthread_join ====================================

// void* func(){
//     pthread_t myself = pthread_self();  
//     printf("the pthread_t of myself is: %lu \n", myself);
// }
// int main(int argc, char * argv[]){
//     pthread_t th[5];
//     for (int i=0; i<5; i++){
//         pthread_create(th+i, NULL, &func, NULL);
//         printf("the %d-th thread created\n", i);
//     }

//     // for (int i=0; i<5; i++){
//     //     pthread_join(th[i],NULL);
//     //     printf("the %d-th thread terminated\n", i);
//     // }
//     return 0;
// }
// in this case, the number of created threads is not equal to the number of running threads sometimes. 
// This is because the main thread is not waiting for the terminations of all created threads. 
// If the main function executes 'return 0;' before the running of some threads, these threads will be killed 
// by the process (since the process is terminated).
// !!: the main function has two meanings: 1. the process; 2. the main thread.
// The pthread_join (pthread_t thread_id, void ** value_ptr) has two functions: 
//            1. Blocking the main thread until the thread <thread_id> terminated and returns values; 
//            2. Release the resources that are allocated to thread <thread_id>;





// ============================== 4: pthread_exit and pthread_detach ====================================

// >>>> 4.1 Exit the main thread while keeping the other threads running. ------------------------------

// void* func(){
//     pthread_t myself = pthread_self();  
//     sleep(5);
//     printf("the pthread_t of myself is: %lu \n", myself);
//     pthread_exit(0);
// }
// int main(int argc, char * argv[]){
//     pthread_t th[10];
//     for (int i=0; i<10; i++){
//         pthread_create(th+i, NULL, &func, NULL);
//         pthread_detach(*(th+i));
//         printf("the %d-th thread created\n", i);
//     }

//     // for (int i=0; i<10; i++){
//     //     pthread_join(th[i],NULL);
//     //     printf("the %d-th thread terminated\n", i);
//     // }
//     printf("close the main thread!\n");
//     return 0;
// }
// Since we terminate the main thread, the resources allocated to the created threads 
// can not be released by the main thread (via the pthread_join()).
// We need to let the thread release its resources when it is terminated automatically.
// The only thing that we need to do is to set the created threads to be 
// detached by using API: pthread_detach()

// >>>> 4.2 Another way to intialize detached thread. ------------------------------

// void* func(){
//     pthread_t myself = pthread_self();  // Similar with the getpid() in process
//     sleep(5);
//     printf("the pthread_t of myself is: %lu \n", myself);
//     pthread_exit(0);
// }
// int main(int argc, char * argv[]){
//     pthread_t th[10];
//     pthread_attr_t detached_state;
//     pthread_attr_init(&detached_state);
//     pthread_attr_setdetachstate(&detached_state, PTHREAD_CREATE_DETACHED);

//     for (int i=0; i<10; i++){
//         pthread_create(th+i, &detached_state, &func, NULL);
//         // pthread_detach(*(th+i));
//         printf("the %d-th thread created\n", i);
//     }

//     // for (int i=0; i<10; i++){
//     //     pthread_join(th[i],NULL);
//     //     printf("the %d-th thread terminated\n", i);
//     // }
//     printf("close the main thread!\n");
//     pthread_exit(0);
// }




// ============================== 5: passing arguments to created thread ====================================

// >>> 5.1: passing an argument to a thread ----------------------------------------

// void* func(void* argc){
//     printf("The received argument is: %c\n", *(char*) argc);
// }

// int main(int argc, char * argv[]){
//     pthread_t thread1;
//     char* c = "A";
//     pthread_create(&thread1, NULL, &func, (void*) c);
//     pthread_join(thread1,NULL);
//     return 0;
// }

// >>>> 5.2: passing an array to a thread ------------------------------------------------

// void* func(void* argc){
//     int* array_head = (int*) argc;
//     for (int i=1; i<5; i++){
//         printf("%d",*array_head);
//         array_head++;
//     }
//     printf("\n");
// }

// int main(int argc, char * argv[]){
//     pthread_t thread1;
//     int c[4] = {1,2,3,4};
//     pthread_create(&thread1, NULL, &func, (void*) c);
//     pthread_join(thread1,NULL);
//     return 0;
// }

// >>>> 5.3: passing an array to multiple threads ------------------------------------------------
// Consider an array with 10 elements, we pass this array to 5 threads, 
// the first thread gets the first two elements, 
// the second thread gets the second two elements, and so forth.

// void* func(void* argc){
//     int* array_head = (int*) argc;
//     printf("Received Elements are: %d, %d",*array_head, *(array_head+1));
//     printf("\n");
// }

// int main(int argc, char * argv[]){
//     pthread_t th[5];
//     int c[10] = {0,1,2,3,4,5,6,7,8,9};
//     for (int i=0; i<5; i++){
//         pthread_create(th+i, NULL, &func, (void*) (c+i*2));
//         printf("the %d-th thread created\n", i);
//     }
//     for (int i=0; i<5; i++){
//         pthread_join(th[i],NULL);
//         printf("the %d-th thread terminated\n", i);
//     }
//     return 0;
// }





// ============================== 6: Get returned value from the created thread. ====================================

// >>>> 6.1: Get returned value from the created thread. (Wrong implementation) ------------------------------------

// void* func(){
//     int value = 5;
//     return (void*) &value;
// }

// int main(int argc, char * argv[]){ 
//     pthread_t thread1;
//     int* return_value;
//     pthread_create(&thread1, NULL, &func, NULL);
//     pthread_join(thread1,(void**) &return_value);
//     printf("the returned value is: %d \n", *return_value);
//     return 0;
// }
// !!: Compile: warning: function returns address of local variable [-Wreturn-local-addr]
// !!: Execution: Segmentation fault (core dumped)
// !!: Reason: the local variable is stored in the thread's stack which is not shared with other threads (e.g., the main thread). 


// >>>> 6.2: Get returned value from the created thread. (Right implementation) -------------------------------------

void* func(){
    int value = 5;
    int* result = malloc(sizeof(int));
    *result = value;
    printf("Thread: The returned value is %d\n",value);
    printf("Thread: The address of the returned value <result> %p\n",result);
    return (void*) result;
}

int main(int argc, char * argv[]){ 
    pthread_t thread1;
    int* return_value;
    pthread_create(&thread1, NULL, &func, NULL);
    pthread_join(thread1,(void**) &return_value);
    printf("Main: The returned value is %d\n",*return_value);
    printf("Main: The address of the returned value <return_value> %p\n",return_value);
    free(return_value);
    return 0;
}
// !!: Reason: in the func(), we allocate a space of the heap to store the returned value, 
// and the heap is shared by all threads of the same process. 
