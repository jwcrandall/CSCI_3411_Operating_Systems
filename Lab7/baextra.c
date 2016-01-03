#include "bankersAlgorithm.h"

void *threadFunction(void *data){
	// printf("Hello\n");
	// pthread_exit(0);

	//sleep(1);  // need unistd
	int passedInt = *((int *)data);

	printf("the number passed to me is %d\n", passedInt);


	//free the space when the thread is done using it
	free((int *)data);
	pthread_exit(0);
}

void createThread(pthread_t *threadID){
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	//int i = 100;
	int *intPtr = malloc(sizeof(int));

	*intPtr = 100;

	pthread_create(threadID, &attr, threadFunction, intPtr);

}


