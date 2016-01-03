#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void*threadFunction(void*);
void createThread(pthread_t*);

int main(){
	pthread_t threadID;
	pthread_attr_t attr;

	// pthread_attr_init(&attr); //set attr to default value

	// pthread_create(&threadID, &attr, threadFunction, NULL);
	createThread(&threadID);

	pthread_join(threadID, NULL);
}

void createThread(pthread_t *threadID){
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	//int i = 100;
	int *intPtr = malloc(sizeof(int));

	*intPtr = 100;

	pthread_create(threadID, &attr, threadFunction, intPtr);

}


void *threadFunction(void *data){
	// printf("Hello\n");
	// pthread_exit(0);

	sleep(1);  // need unistd
	int passedInt = *((int *)data);

	printf("the number passed to me is %d\n", passedInt);


	//free the space when the thread is done using it
	free((int *)data);
	pthread_exit(0);
}