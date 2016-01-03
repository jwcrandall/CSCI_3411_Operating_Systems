#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>



//declares ahead of time
void *runner (void *threadParams);
void *runner2 (void *threadParams);


//idea that you can add half the numbers in one thread then add the other half in the other thread and
int partialSum[2] = {0,0};
int total sum;


int main(){
    pthread_t thread1, thread2;
    pthread_attr_t attr;
    char *x = "10";

    int thread1[][];
    int thread2[][];

    //Default attributes
    pthread_attr_init(&attr);

    //Create and start thread
    pthread_create(&tid, &attr, runner, x);

    //Wait for thread to finish
    pthread_join(tid, NULL);

    printf("Sum = %d\n", sum);
}

int*lower=(int*)params[0];

//Threads should run this function
void *runner(void *params){
    int i;
    int upper;
    sum = 0;

    //param contains &x
    upper = atoi((char*)params);

    //Sums up numbers from 1 - upper
    for(i = 1; i <= upper; i++)
        sum += i;
    pthread_exit(0);
}