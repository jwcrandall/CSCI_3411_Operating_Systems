#include "bankersAlgorithm.h"


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

void printSystemState(functionData *data){

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
			printf("%d ",data->allocation[tp][ajp]);
		}
		printf("		");
        for(int mjp = 0; mjp < NUMBER_OF_RESOURCES; mjp++){
			printf("%d ",data->maximum[tp][mjp]);
		}
		printf("	");
		for(int njp = 0; njp < NUMBER_OF_RESOURCES; njp++){
			printf("%d ",data->need[tp][njp]);
		}
		printf("	");
        if(tp == 0){
        	for(int j = 0; j < NUMBER_OF_RESOURCES; j++) {
        	printf("%d ", data->available[j]);
        	}
    	}
    }
    printf("\n\n");

}

//still need to take care of rejection
int safteyRecursive(functionData *data, safteyData *sdata){

	//function data
	functionData *mydata = data;
	//saftey data
	safteyData *mysdata = sdata;


	for(int i = 0; i < NUMBER_OF_THREADS; i++){
		//printf("new loop\n");
		if(mysdata->Finish[i] == 0){
			//boolean work greater than need checker
			int gwn = 0;
			for(int j = 0; j < NUMBER_OF_RESOURCES; j++){
					if (mysdata->Work[j] >= mydata->need[i][j]){
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
					mysdata->Work[a] = mysdata->Work[a] + mydata->allocation[i][a];
				}
				//finish update
				mysdata->Finish[i] = 1;
				//saftey seqeuce update
				mysdata->ssposition = mysdata->ssposition + 1;
				mysdata->SafteySequence[mysdata->ssposition] = i;
				//check if saftey sequency is full
				if (mysdata->ssposition == NUMBER_OF_THREADS - 1){
					printf("Request is granted. System is safe state with sequencey: [");
					for (int b = 0 ; b < NUMBER_OF_THREADS; b++){
						printf("P%d ", mysdata->SafteySequence[b]);
					}
					printf("]\n");
					//set the saftey state

					mydata->safteyState = 1;

					//printf("%d\n" ,mysdata->ssposition);


					printf("System State:\n");
					printSystemState(mydata);

					return 1;
				}

				else{
					int boolean = safteyRecursive(mydata, mysdata);
											//printf("%d\n" ,mydata->safteyState);
				//												printf("%d\n" ,boolean);


					if(boolean != 1){
						//work
						for(int a = 0; a<NUMBER_OF_RESOURCES; a++){
							mysdata->Work[a] = mysdata->Work[a] - mydata->allocation[i][a];
						}
						//saftey state null
						mysdata->SafteySequence[mysdata->ssposition] = 100;
						//ss decrease
						mysdata->ssposition = mysdata->ssposition - 1;
						return 0;
					}
					else
						return 1;
				}
			}
		}
	}
	return 0;
}

//saftey first
int saftey(functionData *data){
	functionData *mydata = data;
	//mydata = *((functionData *)data);

	safteyData *sdata = malloc(sizeof(safteyData));

	//initilize work
	for (int i  = 0; i < NUMBER_OF_RESOURCES; i++){
		sdata->Work[i] = mydata->available[i];
	//printf("%d   %d\n",sdata->Work[i],mydata->available[i]);

	}
	//initilize Finish
	for (int j = 0; j < NUMBER_OF_THREADS; j++){
		sdata->Finish[j] = 0;
	}

	//printf("%d   %d\n",sdata->Work[0],mydata->need[0][0]);

	//inital values
	sdata->Finish[mydata->currentId] = 1;
	sdata->SafteySequence[0] = mydata->currentId;
	sdata->ssposition = 0;

	mydata->safteyState = safteyRecursive(mydata, sdata);

	if(mydata->safteyState == 1){
		//printf("Here + %d\n", mydata->safteyState);
		return 1;
	}
	else
		return 0;

	free(sdata);

}

void resourceRequest(functionData *data){

	functionData *mydata = data;
	//get more clarification

	//request less than available
	int rla = 0;
	for(int j = 0; j < NUMBER_OF_RESOURCES; j++){
		if (mydata->request[j] <= mydata->available[j]){

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
			mydata->available[a] = mydata->available[a] - mydata->request[a];
			//allocation = allocation + request
			mydata->allocation[mydata->currentId][a] = mydata->allocation[mydata->currentId][a] + mydata->request[a];
			//need = need - request
			mydata->need[mydata->currentId][a] = mydata->need[mydata->currentId][a] - mydata->request[a];
		}
		//TESTING printSystemState(&mydata);
		//TESTING sleep(1000);
		//if with these values we have a safe state, print and done
		mydata->safteyState = 0;
		mydata->safteyState = saftey(mydata);

		//printf("%d\n" ,mydata->safteyState);

		//if not
		//printSystemState(&mydata);
		if (mydata->safteyState == 0){
			//printf("high on the stack\n");
			for(int b = 0; b<NUMBER_OF_RESOURCES;b++){
				//all independent, order does not matter
				//need = need + request
				mydata->need[mydata->currentId][b] = mydata->need[mydata->currentId][b] + mydata->request[b];
				//allocation = allocation - request
				mydata->allocation[mydata->currentId][b] = mydata->allocation[mydata->currentId][b] - mydata->request[b];
				//available = available + requet
				mydata->available[b] = mydata->available[b] + mydata->request[b];
			}
		}
	}
	//return &mydata;
//printSystemState(&mydata);
}

void resourceRelease(functionData *data){
	//srand(time(NULL));

	functionData *mydata = data;
	//mydata = *((functionData *)data); //get more clarification

	int releaseing[NUMBER_OF_RESOURCES];

	for (int i = 0; i < NUMBER_OF_RESOURCES; i++){
		if(mydata->allocation[mydata->currentId][i] == 0){
			releaseing[i] = 0;
		}
		else{
			releaseing[i] = rand() % (mydata->allocation[mydata->currentId][i]);
		}
		mydata->allocation[mydata->currentId][i] = mydata->allocation[mydata->currentId][i] - releaseing[i];
		mydata->need[mydata->currentId][i] = mydata->need[mydata->currentId][i] + releaseing[i];
		mydata->available[i] = mydata->available[i] + releaseing[i];
	}

	printf("P%d is releasing: [ ", mydata->currentId);
	for (int j = 0 ; j < NUMBER_OF_RESOURCES; j++){
		printf("%d ", releaseing[j]);
	}
	printf("]\n");
	printf("System State:\n");
	printSystemState(mydata);

}

//the bank is open
void bankers(functionData *data){
	functionData *mydata = data;
	//mydata = *((functionData *)data); //get more clarification


	resourceRequest(mydata);
	//printSystemState(&mydata);

	sleep(1);

	if(mydata->safteyState == 1){
		resourceRelease(mydata);
	}
	else{
		printf("State not safe, cannot give resource\n");
	}
	//saftey algorithm
	//saftey(&mydata);
	//printSystemState(&mydata);
	//resource allocation allgorithm
	//return &mydata;
}

void thread(void *data){

	srand(time(NULL));

	functionData *mydata = (functionData *)data;

	int id  = mydata->currentId;

	//int request[NUMBER_OF_RESOURCES];
	for(int i = 0; i< NUMBER_OF_RESOURCES; i++){
		//random number with upper bound need
		if(mydata->need[id][i] == 0){
			mydata->request[i] = 0;
		}
		if(mydata->need[id][i] != 0){
			mydata->request[i] = rand() % (mydata->need[id][i]);
		}
	}
	printf("P%d is requesting: [ ", id);
	for (int j ; j < NUMBER_OF_RESOURCES; j++){
		printf("%d ", mydata->request[j]);
	}
	printf("]\n");

	bankers(mydata);
	//printSystemState(&mydata);
	//pthread_exit(0);
	//return (void *)&mydata;

}

//read command line arguments
int main(int argumentCount, char *argumentArray[]){

	functionData *data = malloc(sizeof(functionData));

	srand(time(NULL));

	//initlize arrays
	//initilize available
	int available[NUMBER_OF_RESOURCES];
	for(int i = 1; i < argumentCount; i++){
		// this might not work
		data->available[i-1] = atoi(argumentArray[i]);
	}
	//initialize max
	int min = 0;
	int maximum[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	for(int mi = 0; mi < NUMBER_OF_THREADS; mi++){
		for(int mj = 0; mj < NUMBER_OF_RESOURCES; mj++){
			data->maximum[mi][mj] = rand() % data->available[mj];
		}
	}
	//initialize allocation
	int allocation[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	for(int ai = 0; ai < NUMBER_OF_THREADS; ai++){
		for(int aj = 0; aj < NUMBER_OF_RESOURCES; aj++){
			 data->allocation[ai][aj] = 0;
		}
	}
	//initialize neede
	int need[NUMBER_OF_THREADS][NUMBER_OF_RESOURCES];
	for(int ni = 0; ni < NUMBER_OF_THREADS; ni++){
		for(int nj = 0; nj < NUMBER_OF_RESOURCES; nj++){
			data->need[ni][nj] = data->maximum[ni][nj] - data->allocation[ni][nj];
		}
	}
	//initialize Thread Numbers
	int threadNumbers[NUMBER_OF_THREADS];
	for (int nti = 0; nti < NUMBER_OF_THREADS; nti++){
		data->threadNumbers[nti] = nti;
	}

//print the intial state
	printf("\nInitial System State:\n");
	printSystemState(data);

//making and launching the threads

    pthread_t *threadIds;
	pthread_attr_t attr;
	threadIds = malloc(sizeof(pthread_t) * NUMBER_OF_THREADS);
	pthread_attr_init(&attr);
	for(int i = 0;i<20;i++){
		for (int pt = 0; pt < NUMBER_OF_THREADS; pt++){
			data->currentId = pt;
			//create thread
			pthread_create(&threadIds[pt], &attr, thread, data);
			//join theads
			//your threads need to wait for each other, that is why you have to tell threads to wait
			pthread_join(threadIds[pt], NULL);
			//printSystemState(data);
		}
	}
}