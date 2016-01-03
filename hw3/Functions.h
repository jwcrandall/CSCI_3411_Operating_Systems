#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


//bankers algortihm

//pthread
void*threadFunction(void*);

void createThread(pthread_t*);

//random number generation between bounds
unsigned int randInterval(unsigned int min, unsigned int max);

int toto(int value);