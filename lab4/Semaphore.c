#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

#define SIZE 100
#define THREAD_COUNT 10
#define SLEEP_TIME 1

void *printer (void *params);

int threadCount = 0;

sem_t threadSem, counterSem;

int main(int argc, char **argv){
    int i;
    pthread_t threadIDs[THREAD_COUNT];
    pthread_attr_t attr;

    pthread_attr_init(&attr);

//    sem_init(&semaphore, 0,5);

    sem_init(&threadSem, 0, 3);
    sem_init(&counterSem, 0, 1);
    for(i = 0; i < THREAD_COUNT; i ++)
        pthread_create(&threadIDs[i], &attr, printer, NULL);

//    sem_destory(&semaphore);


    for(i = 0; i < THREAD_COUNT; i ++)
        pthread_join(threadIDs[i], NULL);

    printf("All threads complete!\n");
}

void *printer(void *params){

    //threadsem.wait intilized 3
    sem_wait(&threadSem)
    sem_wait(&counterSem)


    threadCount++;
    printf("Thread %d executing\n", threadCount);

   // countSem.wait initilzied 1
    sem_post(&counterTime);


    sleep(SLEEP_TIME);
//threadsem.postending the semaphore
    sem_post(&threadSem);


    pthread_exit(0);


}