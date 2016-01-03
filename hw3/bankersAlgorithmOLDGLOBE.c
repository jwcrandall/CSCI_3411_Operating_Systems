#include "bankersAlgorithm.h"
#include "Functions.h"

	//int NUMBER_OF_RESOURCES;
	int available[NUMBER_OF_RESOURCES];
	int maximum[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	int allocation[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	int need[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	int threadNumbers[NUMBER_OF_THREADS];
	int currentId;
	int request[NUMBER_OF_RESOURCES];
	int safteyState;

typedef struct
{
	// //int NUMBER_OF_RESOURCES;
	// int available[NUMBER_OF_RESOURCES];
	// int maximum[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	// int allocation[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	// int need[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	// int threadNumbers[NUMBER_OF_THREADS];
	// int currentId;
	// int request[NUMBER_OF_RESOURCES];
	// int safteyState;

}functionData;

typedef struct
{
	int Work[NUMBER_OF_RESOURCES];
	int Finish[NUMBER_OF_THREADS];
	int SafteySequence[NUMBER_OF_THREADS];
	int ssposition;

}safteyData;

void printSystemState(int available[NUMBER_OF_RESOURCES],
						int maximum[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES],
						int need[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES],
						int allocation[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES]){
	// functionData mydata;
	// mydata = *((functionData *)data); //get more clarification

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
			printf("%d ",allocation[tp][ajp]);
		}
		printf("		");
        for(int mjp = 0; mjp < NUMBER_OF_RESOURCES; mjp++){
			printf("%d ",maximum[tp][mjp]);
		}
		printf("	");
		for(int njp = 0; njp < NUMBER_OF_RESOURCES; njp++){
			printf("%d ",need[tp][njp]);
		}
		printf("	");
        if(tp == 0){
        	for(int j = 0; j < NUMBER_OF_RESOURCES; j++) {
        	printf("%d ", available[j]);
        	}
    	}
    }
    printf("\n\n");

}

//still need to take care of rejection
int *safteyRecursive(void* data, void* sdata){

	//function data
	functionData mydata;
	mydata = *((functionData *)data);
	//saftey data
	safteyData mysdata;
	mysdata = *((safteyData *)sdata);


	for(int i = 0; i < NUMBER_OF_THREADS; i++){
		//printf("new loop\n");
		if(mysdata.Finish[i] == 0){
			//boolean work greater than need checker
			int gwn = 0;
			for(int j = 0; j < NUMBER_OF_RESOURCES; j++){
					if (mysdata.Work[j] >= need[i][j]){
						//printf("if true\n");

						gwn = 1;
					}
					else{
						gwn =0;
						//printf("break\n");
						break;
					}
				}
			if(gwn == 1){
				//work addition
				for(int a = 0; a<NUMBER_OF_RESOURCES; a++){
					mysdata.Work[a] = mysdata.Work[a] + allocation[i][a];
				}
				//finish update
				mysdata.Finish[i] = 1;
				//saftey seqeuce update
				mysdata.ssposition = mysdata.ssposition + 1;
				mysdata.SafteySequence[mysdata.ssposition] = i;
				//check if saftey sequency is full
				if (mysdata.ssposition == NUMBER_OF_THREADS - 1){
					printf("Request is granted. System is safe state with sequencey: [");
					for (int b = 0 ; b < NUMBER_OF_THREADS; b++){
						printf("P%d ", mysdata.SafteySequence[b]);
					}
					printf("]\n");
					//set the saftey state

					safteyState = 1;

					printf("%d\n" ,mysdata.ssposition);


					printf("System State:\n");
					//printSystemState(&mydata);

					return 1;
				}

				else{
					int boolean = safteyRecursive(&mydata, &mysdata);
											//printf("%d\n" ,safteyState);
				//												printf("%d\n" ,boolean);


					if(boolean != 1){
						//work
						for(int a = 0; a<NUMBER_OF_RESOURCES; a++){
							mysdata.Work[a] = mysdata.Work[a] - allocation[i][a];
						}
						//saftey state null
						mysdata.SafteySequence[mysdata.ssposition] = NULL;
						//ss decrease
						mysdata.ssposition = mysdata.ssposition - 1;
						return 0;
					}
					else
						return 1;
				}
			}
		}
	}
}

//saftey first
int *saftey(void *data){
	functionData mydata;
	mydata = *((functionData *)data);

	safteyData sdata;

	//initilize work
	for (int i  = 0; i < NUMBER_OF_RESOURCES; i++){
	sdata.Work[i] = available[i];
	//printf("%d   %d\n",sdata.Work[i],available[i]);

	}
	//initilize Finish
	for (int j = 0; j < NUMBER_OF_RESOURCES; j++){
	sdata.Finish[j] = 0;
	}

	//printf("%d   %d\n",sdata.Work[0],need[0][0]);

	//inital values
	sdata.Finish[currentId] = 1;
	sdata.SafteySequence[0] = currentId;
	sdata.ssposition = 0;

	safteyState = safteyRecursive(&mydata, &sdata);

	if(safteyState == 1){
		//printf("Here + %d\n", safteyState);
		return 1;
	}
	else
		return 0;


}

functionData *resourceRequest(void* data){

	functionData mydata;
	mydata = *((functionData *)data); //get more clarification

	//request less than available
	int rla = 0;
	for(int j = 0; j < NUMBER_OF_RESOURCES; j++){
		if (request[j] <= available[j]){

			rla = 1;
		}
		else{

			rla =0;
			break;
		}
	}
	//printf("high on stack %d\n", rla);
	if(rla == 1){
		for(int a = 0; a<NUMBER_OF_RESOURCES; a++){
			//availble = available - request
			available[a] = available[a] - request[a];
			//allocation = allocation + request
			allocation[currentId][a] = allocation[currentId][a] + request[a];
			//need = need - request
			need[currentId][a] = need[currentId][a] - request[a];
		}
		//TESTING printSystemState(&mydata);
		//TESTING sleep(1000);
		//if with these values we have a safe state, print and done
		safteyState = 0;
		safteyState = saftey(&mydata);

		//printf("%d\n" ,safteyState);

		//if not
		//printSystemState(&mydata);
		if (safteyState == 0){
			printf("high on the stack\n");
			for(int b = 0; b<NUMBER_OF_RESOURCES;b++){
				//all independent, order does not matter
				//need = need + request
				need[currentId][b] = need[currentId][b] + request[b];
				//allocation = allocation - request
				allocation[currentId][b] = allocation[currentId][b] - request[b];
				//available = available + requet
				available[b] = available[b] + request[b];
			}
		}
	}
	return &mydata;
//printSystemState(&mydata);
}

void *resourceRelease(void *data){
	//srand(time(NULL));

	functionData mydata;
	mydata = *((functionData *)data); //get more clarification

	int releaseing[NUMBER_OF_RESOURCES];

	for (int i = 0; i < NUMBER_OF_RESOURCES; i++){
		if(allocation[currentId][i] == 0){
			releaseing[i] == 0;
		}
		else{
			releaseing[i] = rand() % (allocation[currentId][i]);
		}
		allocation[currentId][i] = allocation[currentId][i] - releaseing[i];
		need[currentId][i] = need[currentId][i] + releaseing[i];
		available[i] = available[i] + releaseing[i];
	}

	printf("P%d is releasing: [ ", currentId);
	for (int j = 0 ; j < NUMBER_OF_RESOURCES; j++){
		printf("%d ", releaseing[j]);
	}
	printf("]\n");
	printf("System State:\n");
	//printSystemState(&mydata);

}

//the bank is open
functionData *bankers(void *data){
	functionData mydata;
	mydata = *((functionData *)data); //get more clarification


	mydata = *resourceRequest(&mydata);
	//printSystemState(&mydata);

	sleep(1);

	if(safteyState = 1){
		resourceRelease(&mydata);
	}
	//saftey algorithm
	//saftey(&mydata);
	//printSystemState(&mydata);
	//resource allocation allgorithm
	return &mydata;
}

void *thread(int need[NUMBER_OF_THREADS][NUMBER_OF_THREADS]){

	srand(time(NULL));

//	functionData mydata;
//	mydata = *((functionData *)data); //get more clarification

	int id  = currentId;

	//int request[NUMBER_OF_RESOURCES];
	for(int i = 0; i< NUMBER_OF_RESOURCES; i++){
		//random number with upper bound need
		if(need[id][i] == 0){
			request[i] = 0;
		}
		if(need[id][i] != 0){
		request[i] = rand() % (need[id][i]);
		}
	}

	printf("P%d is requesting: [ ", id);
	for (int j = 0 ; j < NUMBER_OF_RESOURCES; j++){
		printf("%d ", request[j]);
	}
	printf("]\n");

	//mydata = *bankers(&mydata);
	//printSystemState(&mydata);
	//pthread_exit(0);
	//return (void *)&mydata;

}

//read command line arguments
int main(int argumentCount, char *argumentArray[]){

	functionData *data;

	srand(time(NULL));

	//initlize arrays
	//initilize available
	int available[NUMBER_OF_RESOURCES];
	for(int i = 1; i < argumentCount; i++){
		// this might not work
		available[i-1] = atoi(argumentArray[i]);
	}
	//printf("%d\n",available[0] );
	//initialize max
	int min = 0;
	int maximum[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	for(int mi = 0; mi < NUMBER_OF_THREADS; mi++){
		for(int mj = 0; mj < NUMBER_OF_RESOURCES; mj++){
			maximum[mi][mj] = rand() % available[mj];
		}
	}
	//initialize allocation
	int allocation[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	for(int ai = 0; ai < NUMBER_OF_THREADS; ai++){
		for(int aj = 0; aj < NUMBER_OF_RESOURCES; aj++){
			 allocation[ai][aj] = 0;
		}
	}
	//initialize neede
	int need[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	for(int ni = 0; ni < NUMBER_OF_THREADS; ni++){
		for(int nj = 0; nj < NUMBER_OF_RESOURCES; nj++){
			need[ni][nj] = maximum[ni][nj] - allocation[ni][nj];
		}
	}
	//initialize Thread Numbers
	int threadNumbers[NUMBER_OF_THREADS];
	for (int nti = 0; nti < NUMBER_OF_THREADS; nti++){
		threadNumbers[nti] = nti;
	}

//print the intial state
	printf("\nInitial System State:\n");
	printSystemState(available,maximum,need,allocation);

//making and launching the threads

     pthread_t *threadIds;
	 pthread_attr_t attr;
	 threadIds = malloc(sizeof(pthread_t) * NUMBER_OF_THREADS);
	 pthread_attr_init(&attr);
	 for (int pt = 0; pt < NUMBER_OF_THREADS; pt++){
	 	currentId = pt;
	 	//create thread
	 	pthread_create(&threadIds[pt], &attr, thread,need);
	 	//join theads
	 	//your threads need to wait for each other, that is why you have to tell threads to wait
	 	pthread_join(threadIds[pt], NULL);
	 	//printSystemState(available,maximum,need,allocation);
	}
}