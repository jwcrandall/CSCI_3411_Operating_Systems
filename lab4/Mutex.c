#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE 100
#define THREAD_COUNT 10
#define SLEEP_TIME 1

void *printer (void *params);
//global thread
int threadCount = 0;


//create your mutex, should it be as a global
pthread_mutex_t mutex;



int main(int argc, char **argv){
    int i;
    //array of pthread_t (holds 10 thread ID numbers)
    pthread_t threadIDs[THREAD_COUNT];
    //Attributes variables
    pthread_attr_t attr;
    //sets the attributes to default values
    pthread_attr_init(&attr);






pthread_mutex_init(&mutex, NULL);


    //create 10 threads
    for(i = 0; i < THREAD_COUNT; i ++)
        pthread_create(&threadIDs[i], &attr, printer, NULL);

    //Parent waits for each thread to finish
    for(i = 0; i < THREAD_COUNT; i ++)
        pthread_join(threadIDs[i], NULL);

pthread_mutex_destory(&mutex);

    printf("All threads complete!\n");
}




//Fucntion returns void* and takes void* as parameter
//return type / name / parameters
void *printer(void *params){
    //increment the thread count

//add a lock
pthread_mutex_lock(&mutex);

    threadCount++;
    printf("Thread %d started\n", threadCount);

    //waiting for 1 second
    sleep(SLEEP_TIME);

    //
    printf("Thread %d done\n", threadCount);

pthread_mutex_unlock(&mutex);
//unlock here



    pthread_exit(0);
}