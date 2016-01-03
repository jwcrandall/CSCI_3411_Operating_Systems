// /*thes may be any vlaues >= 0*/
// #define NUMBER_OF_THREADS 5
// #define NUMBER_OF_RESOURCES 3
#include "bankersAlgorithm.h"
#include "Functions.h"
//#include "randomNumer.c"
//#define NUMBER_OF_THREADS 5


//void pointer function
void foo(void *);

typedef struct
{
	//int NUMBER_OF_RESOURCES;
	int available[NUMBER_OF_RESOURCES];
	int maximum[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	int allocation[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	int need[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	int threadNumbers[NUMBER_OF_THREADS];
}functionData;



//random number within bounds
unsigned int randInterval(unsigned int min, unsigned int max){
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

int rand_lim(int limit) {
//return a random number between 0 and limit inclusive.
    int divisor = RAND_MAX/(limit+1);
    int retval;

    do {
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}

void *thread(void* data){


	int id;
	void **ptrArr = (void **)data;
	id = *((int *)ptrArr[0]);
	printf("P%d is requesting: \n", id);
	pthread_exit(0);





	//create threads

	//loop
	//random requests withing each (random 0-need)

	//random request ->
	//sleep
	//random_release (can release anything between what it takes and zero)

}

// void *voidPointer bankers(void* data){
// 	//saftey
// 		// work and allocate
// 		//is their a safe sequence
// 	//resource allocation (rand(0->max-all))
// }

// void *voidPointer saftey(void* data)_RESOURCES				Finish[i] = 1;
// 					//update the satey seqeunce
// 					safteySequence[postion] = threadNumbers[i] //the process number at finish I;
// 					position++;


// 				}
// 			}
// 		}
// }

void printSystemState(void *data){
	functionData mydata;
	mydata = *((functionData *)data);

	//processor(thread list)
	//array of array names
    char *arrayNames[] = {
        "Allocation", "Max",
        "Need", "Available"
    };
 	char *processors[] = {
        "P0", "P1", "P2", "P3","P4"
    };
    int num_arrays = 4;
    for(int iaa = 0; iaa < num_arrays; iaa++) {
        printf("	%s",arrayNames[iaa]);
    }
    for(int tp = 0; tp < NUMBER_OF_THREADS; tp++) {
        printf("\n%s", processors[tp]);
        printf("	");
        for(int ajp = 0; ajp < NUMBER_OF_RESOURCES; ajp++){
			printf("%d ",mydata.allocation[tp][ajp]);
		}
		printf("		");
        for(int mjp = 0; mjp < NUMBER_OF_RESOURCES; mjp++){
			printf("%d ",mydata.maximum[tp][mjp]);
		}
		printf("	");
		for(int njp = 0; njp < NUMBER_OF_RESOURCES; njp++){
			printf("%d ",mydata.need[tp][njp]);
		}
		printf("	");
        if(tp == 0){
        	for(int j = 0; j < NUMBER_OF_RESOURCES; j++) {
        	printf("%d ", mydata.available[j]);
        	}
    	}
    }
    printf("\n\n");

}


//read command line arguments
int main(int argumentCount, char *argumentArray[]){

	functionData data;

	srand(time(NULL));

	//initlize arrays
	//initilize available
	int available[NUMBER_OF_RESOURCES];
	for(int i = 1; i < argumentCount; i++){
		// this might not work
		data.available[i-1] = atoi(argumentArray[i]);
	}
	//initialize max
	int min = 0;
	int maximum[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	for(int mi = 0; mi < NUMBER_OF_THREADS; mi++){
		for(int mj = 0; mj < NUMBER_OF_RESOURCES; mj++){
			data.maximum[mi][mj] = rand() % data.available[mj];
		}
	}
	//initialize allocation
	int allocation[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	for(int ai = 0; ai < NUMBER_OF_THREADS; ai++){
		for(int aj = 0; aj < NUMBER_OF_RESOURCES; aj++){
			 data.allocation[ai][aj] = 0;
		}
	}
	//initialize neede
	int need[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	for(int ni = 0; ni < NUMBER_OF_THREADS; ni++){
		for(int nj = 0; nj < NUMBER_OF_RESOURCES; nj++){
			data.need[ni][nj] = data.maximum[ni][nj] - data.allocation[ni][nj];
		}
	}
	//initialize Thread Numbers
	int threadNumbers[NUMBER_OF_THREADS];
	for (int nti = 0; nti < NUMBER_OF_THREADS; nti++){
		data.threadNumbers[nti] = nti;
	}

	printf("\nInitial System State:\n");
	printSystemState(&data);

//making the threads

    pthread_t *threadIds;
	pthread_attr_t attr;
	threadIds = malloc(sizeof(pthread_t) * NUMBER_OF_THREADS);
	pthread_attr_init(&attr);
	for (int pt = 0; pt < NUMBER_OF_THREADS; pt++){
		//using void pointer array
		void **voidPtrArr = malloc(sizeof(void *) * 2);
		int *spaceForpt = malloc(sizeof(int));
		*spaceForpt = pt;
		voidPtrArr[0] = spaceForpt;
		//create thread
		pthread_create(&threadIds[pt], &attr, thread, voidPtrArr);
	}

















	// printf("available array\n");
	//  for(int j = 0; j < NUMBER_OF_RESOURCES; j++) {
 //        printf("%d ", available[j]);
 //    }
 //    printf("maximum array\n");
	// for(int mip = 0; mip < NUMBER_OF_THREADS; mip++){
	// 	printf("\n");
	// 	for(int mjp = 0; mjp < NUMBER_OF_RESOURCES; mjp++){
	// 		printf("%d",maximum[mip][mjp]);
	// 	}
	// }
	// printf("allocation array\n");
	// for(int aip = 0; aip < NUMBER_OF_THREADS; aip++){
	// 	printf("\n");
	// 	for(int ajp = 0; ajp < NUMBER_OF_RESOURCES; ajp++){
	// 		printf("%d",allocation[aip][ajp]);
	// 	}
	// }
	// printf("need print\n");
	// for(int nip = 0; nip < NUMBER_OF_THREADS; nip++){
	// 	printf("\n");
	// 	for(int njp = 0; njp < NUMBER_OF_RESOURCES; njp++){
	// 		printf("%d",need[nip][njp]);
	// 	}
	// }


	//launch threads

	//join threads






















	// /*the maximum demand of each customer*/
	// int maxium[NUMBER_OF_THREADS][argumentCount];

	// /* the amount currently allcoated to each customer */
	// int allocation[NUMBER_OF_THREADS][argumentCount];

	// /*the remaining need of each customer*/
	// int need[NUMBER_OF_THREADS][argumentCount];

	// //read user input

	// //intilize the array
	// //launch thread
	// //join thread
	// int i;
	// printf("number of arguments = %d\n", argumentCount);

	// for (i = 1; i < argumentCount; i++)
	// 	printf("argArray[%d]= %d\n", i, atoi(argumentArray[i]));

	// int argumentCoun = argumentCount - 1;
	// 	//printf("argumentCount = %d\n", argumentCount
//);





//conecting to the thread c file
	// pthread_t threadID;
	// pthread_attr_t attr;

	// // pthread_attr_init(&attr); //set attr to default value

	// // pthread_create(&threadID, &attr, threadFunction, NULL);
	// createThread(&threadID);

	// pthread_join(threadID, NULL);





//I need to initilze the arrays
//with randoom values for each pthread



}

//need to update all four arrays acordingly

/*
create n customer threads that request and release resoruces form the bank
the customers will continually loop, requesting and releaseing random numbers of resoruces
the customers' requests for resoruces will be bounded by their respective values in the need array
the banker will grant a request if it satisfies the saftey algorithm
If a request does not leave the system in a safe state, the banker will deny it.
*/

// int request_resources(int customer_num, int request[]){

// }

// int release_resources(int customer_num, int release[]){

// }
/*
these two functions shoudl return 0 if successfull -1 if unsucessful
multiple threads will concurently access shared data through these two functions.
Therefor, access must be controlled though mutex locks to prevent race conditions

*/

/*
available aray would be initilized to these values
*/