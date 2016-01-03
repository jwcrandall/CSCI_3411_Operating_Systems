#include "bankersAlgorithm.h"
#include "Functions.h"

//void pointer function
//void foo(void *);

typedef struct
{
	//int NUMBER_OF_RESOURCES;
	int available[NUMBER_OF_RESOURCES];
	int maximum[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	int allocation[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	int need[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	int threadNumbers[NUMBER_OF_THREADS];
	int currentId;
	int request[NUMBER_OF_RESOURCES];
	int safteyState;


}functionData;

typedef struct
{
	int Work[NUMBER_OF_RESOURCES];
	int Finish[NUMBER_OF_THREADS];
	int SafteySequence[NUMBER_OF_THREADS];
	int ssposition;
}safteyData;


//still need to take care of rejection
void *safteyRecursive(void* data, void* sdata){
	printf("high on stack\n");
	//function data
	functionData mydata;
	mydata = *((functionData *)data);
	//saftey data
	safteyData mysdata;
	mysdata = *((safteyData *)sdata);

	for(int i; i < NUMBER_OF_THREADS; i++){
		if(mysdata.Finish[i] == 0){
			//boolean work greater than need checker
			int gwn = 0;
			for(int j; j < NUMBER_OF_RESOURCES; j++){
					if (mysdata.Work[j] >= mydata.need[i][j]){
						gwn = 1;
					}
					else{
						gwn =0;
						break;
					}
				}
			if(gwn == 1){
				//work addition
				for(int a; a<NUMBER_OF_RESOURCES; a++){
					mysdata.Work[a] = mysdata.Work[a] + mydata.available[a];
				}
				//finish update
				mysdata.Finish[i] = 1;
				//saftey seqeuce update
				mysdata.ssposition = mysdata.ssposition + 1;
				mysdata.SafteySequence[mysdata.ssposition] = i;
				//check if saftey sequency is full
				if (mysdata.ssposition == NUMBER_OF_THREADS - 1){
					printf("Request is granted. System is safe state with sequencey: [");
					for (int b ; b < NUMBER_OF_RESOURCES; b++){
						printf("%d ", mysdata.SafteySequence[b]);
					}
					printf("]\n");
					//set the saftey state
					mydata.safteyState = 1;
				}
				else safteyRecursive(&mydata, &mysdata);
			}
		}

	}

}

//saftey first
void *saftey(void *data){
	functionData mydata;
	mydata = *((functionData *)data);

	safteyData sdata;
	//initilize work
	for (int i; i < NUMBER_OF_RESOURCES; i++){
	sdata.Work[i] = mydata.available[i];
	}
	//initilize Finish
	for (int j; j < NUMBER_OF_RESOURCES; j++){
	sdata.Finish[j] = 0;
	}

	//inital values
	sdata.Finish[mydata.currentId] = 1;
	sdata.SafteySequence[0] = mydata.currentId;
	sdata.ssposition = 0;

	safteyRecursive(&mydata, &sdata);

}

void *resourceRequest(void* data){
	functionData mydata;
	mydata = *((functionData *)data); //get more clarification

	//request less than available
	int rla = 0;
	for(int j; j < NUMBER_OF_RESOURCES; j++){
		if (mydata.request[j] <= mydata.available[j]){
			rla = 1;
		}
		else{
			rla =0;
			break;
		}
	}
	if(rla == 1){

		for(int a = 0; a<NUMBER_OF_RESOURCES; a++){
			//availble = available - request
			mydata.available[a] = mydata.available[a] - mydata.request[a];
			//allocation = allocation + request
			mydata.allocation[mydata.currentId][a] = mydata.allocation[mydata.currentId][a] + mydata.request[a];
			//need = need - request
			mydata.need[mydata.currentId][a] = mydata.need[mydata.currentId][a] - mydata.request[a];
		}
		//if with these values we have a safe state, print and done
		mydata.safteyState = 0;
		saftey(&data);
		//if not
		if (mydata.safteyState == 0){
			for(int b = 0; b<NUMBER_OF_RESOURCES;b++){
				//all independent, order does not matter
				//need = need + request
				mydata.need[mydata.currentId][b] = mydata.need[mydata.currentId][b] + mydata.request[b];
				//allocation = allocation - request
				mydata.allocation[mydata.currentId][b] = mydata.allocation[mydata.currentId][b] + mydata.request[b];
				//available = available + requet
				mydata.available[b] = mydata.available[b] + mydata.request[b];
			}
		}
	}
}

//the bank is open
void *bankers(void *data){
	functionData mydata;
	mydata = *((functionData *)data); //get more clarification


	resourceRequest(&mydata);

	//saftey algorithm
	//saftey(&mydata);

	//resource allocation allgorithm
}

void *thread(void *data){

	//srand(time(NULL));

	functionData mydata;
	mydata = *((functionData *)data); //get more clarification

	int id  = mydata.currentId;

	//int request[NUMBER_OF_RESOURCES];
	for(int i; i< NUMBER_OF_RESOURCES; i++){
		//random number with upper bound need
		if(mydata.need[id][i] == 0){
			mydata.request[i] = 0;
		}
		if(mydata.need[id][i] != 0){
		mydata.request[i] = rand() % (mydata.need[id][i]);
		}
	}

	printf("P%d is requesting: [ ", id);
	for (int j ; j < NUMBER_OF_RESOURCES; j++){
		printf("%d ", mydata.request[j]);
	}
	printf("]\n");

	bankers(&mydata);

	sleep(1);

	pthread_exit(0);


	//create threads

	//loop
	//random requests withing each (random 0-need)

	//random request ->
	//sleep
	//random_release (can release anything between what it takes and zero)

}

void printSystemState(void *data){
	functionData mydata;
	mydata = *((functionData *)data); //get more clarification

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

//print the intial state
	printf("\nInitial System State:\n");
	printSystemState(&data);

//makinglaunching the threads

    pthread_t *threadIds;
	pthread_attr_t attr;
	threadIds = malloc(sizeof(pthread_t) * NUMBER_OF_THREADS);
	pthread_attr_init(&attr);
	for (int pt = 0; pt < NUMBER_OF_THREADS; pt++){

		//using void pointer array

		// void **voidPtrArr = malloc(sizeof(void *) * 2);
		// int *spaceForpt = malloc(sizeof(int));
		// *spaceForpt = pt;
		// voidPtrArr[0] = spaceForpt;

		//printf("%d\n",pt);
		data.currentId = pt;

		//create thread
		pthread_create(&threadIds[pt], &attr, thread, &data);
		//your threads need to wait for each other, that is why you have to tell threads to wait
		pthread_join(threadIds[pt], NULL);
	}


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