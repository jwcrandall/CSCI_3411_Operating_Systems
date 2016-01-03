#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <pthread.h>

/* program that takes two command line arguments
1) the number of threads to creat
2)the messge that each thread wil print out

Thread Will:
1) Print out their thread number	}Passes to each thread
2) Print out the message			}via void*

Usage: ./a.out N message

*/

void *printingThread(void *);

typedef struct
{
	int id;
	char *message;
}threadData;

int main (int argc, char *argv[]){
	int i, numThreads;
	char *threadMessage;

	pthread_t *threadIds;
	pthread_attr_t attr;

	numThreads = atoi(argv[1]);
	threadMessage = argv[2];

	printf("Number of threads = %d, Thread message = %s\n", numThreads, threadMessage);

	threadIds = malloc(sizeof(pthread_t) * numThreads); // multiplicatoin not pointer

	pthread_attr_init(&attr);

	for(i = 0; i < numThreads; i++){
		// //Prepare data to send to the i-th thread
		// threadData *data = malloc(sizeof(threadData));
		// data->id = i;
		// data->message = threadMessage;

		//using void pointer array
		void **voidPtrArr = malloc(sizeof(void *)*2);

		//give something space when you need
		int *spaceFori = malloc(sizeof(int));
		*spaceFori = i;
		voidPtrArr[0] = spaceFori;
		voidPtrArr[1] = threadMessage;

		//Create thread
		pthread_create(&threadIds[i], &attr, printingThread, voidPtrArr);
	}
}

void *printingThread(void * data){
	int id;
	char* message;
	void **ptrArr = (void **)data;

	id = *((int *)ptrArr[0]);
	message = (char *)ptrArr[1];


	// threadData myData = *((threadData *)data);
	// id = myData.id;
	// message = myData.message;
	printf("I am thread %d: %s\n", id, message);

	pthread_exit(0);

}

//what to do with .a.out 10 5 7




/*

out put to bankers

eveything someone makes a request, print out the request and tell if the request is granted
if request granted
print out the new row for customer 5 allocation
next
max
available

user will tyep ./a.out 10 3 1
you will have 5 ustomers but you still need a way to determine max

allocation is all zeros
max [0-10 ,0-3, 0-1]

*/