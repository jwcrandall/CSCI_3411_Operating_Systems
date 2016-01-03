#include "methods.h"

int main(int argc, char* argv[]){

	//printf("Hello\n");
	char* fileName = argv[1];
	headStart = atoi(fileName);
	printGreen("The Starting Position of the Disk Head: ");
	printf("%d\n", headStart);
	printGreen("Window Size: ");
	printf("%d\n", 100);

	int totalfcfs = 0;
	int totalsstf = 0;
	int totalscan = 0;
	int totalcscan = 0;
	int totallook = 0;
	int totalclook = 0;
	int runs = 0;


	//printBlue("safe");

	start = (node *)malloc(sizeof(node));

	for(int i= 0 ; i<1000 ;i++){

		initialize();
		//print_cylinders();

		//start always points to the first node of the linked list.

		start -> next = NULL;
		start -> prev = NULL;
		//used in order to place values in the head node
		start -> data = -1;

		//printBlue("safe");

		//scheduling algorithms
		//fcfs
		totalfcfs += fcfs(start, headStart);

		//print(start);

		//start = (node *)malloc(sizeof(node));
		start -> next = NULL;
		start -> prev = NULL;
		//used in order to place values in the head node
		start -> data = -1;

		//print(start);

		//printf("\n\n");

		//sstf
		totalsstf += sstf(start, headStart);

		start -> next = NULL;
		start -> prev = NULL;
		start -> data = -1;

		//print(start);

		//scan
		//int test;
		//test = ;
		//totalscan += scan(start,headStart);
		//printBlue("made it");
		printf("hey\n");

		start -> next = NULL;
		start -> prev = NULL;
		start -> data = -1;

		//cscan
		//totalcscan += cscan(start,headStart);
		printf("hey\n");

		start -> next = NULL;
		start -> prev = NULL;
		start -> data = -1;

		//look
		//totallook += look(start,headStart);
		printf("hey\n");

		start -> next = NULL;
		start -> prev = NULL;
		start -> data = -1;

		//clook
		//totalclook += clook(start,headStart);
		printf("hey\n");

		//runs
		runs ++;
	}

	printGreen("Average Head Movements after ");
	printf("%d",runs);
	printGreen(" runs consisting of 1000 random cylinders ranging in value between 0 and 4999 \n");
	//fcfs
	printf("FCFS:     ");
	printf("%d\n", totalfcfs/runs);
	//sstf
	printf("SSTF:     ");
	printf("%d", totalsstf/runs);
	printRed(" check the head movemnet print out, stays at same value for 100 movements\n");
	//scan
	printf("SCAN:     ");
	printf("%d\n", totalscan/runs);
	//cscan
	printf("C-SCAN:   ");
	printf("%d\n", totalcscan/runs);
	//look
	printf("LOOK:     ");
	printf("%d\n", totallook/runs);
	//clook
	printf("C-LOOK:   ");
	printf("%d\n", totalclook/runs);

	printGreen("Done, check README for further explanation\n");
}



