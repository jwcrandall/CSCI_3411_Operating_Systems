#include "methods.h"

int fcfs(node *pointer, int headStart){
	//reset counters and LinkedList
	//void clear();
	int fcfsHeadMovements = 0;
	int arrayTraverse = 0;

	//place first 100 cylindes in linked list
	for(int i = 0 ; i < 100 ; i++){
		arrayTraverse = i;
		insertAtEnd(pointer,cylinders[arrayTraverse]);
		//printf("%d   " , arrayTraverse);
		//printf("%d\n", cylinders[arrayTraverse]);
	}
	//print(pointer);
	//printf("\n\n");


	//go to first elemtn in linked list
	//printf("test\n");
	//printf("%d\n",pointer->data);



//add the differnce of position and next position
//replace current position with next int in array
//move to next position in linked list/

//if you get to the end of the linked list go back to the beging

//after 9 curcuts you will stop adding elemetns becuase you will have traversed the array.

//keep going untill all elements in linked list have been processed and delted



// I have an extra Zero in the Linked list that needs to be removed
// 	int position = headStart;
// 	int move = pointer->next->data;




	//first move
	int firstHeadMovement = abs(headStart - pointer->data);
	//printf("%d\n", firstHeadMovement);
	fcfsHeadMovements = firstHeadMovement ;
	//printf("%d\n", fcfsHeadMovements);

	//printf("%d   " , arrayTraverse);
	//printf("%d\n",fcfsHeadMovements);

while (pointer->next != NULL && pointer->data != -10000){
	//are we at the end of the linked list
	if(pointer->next != NULL){
		//add head movement
		fcfsHeadMovements += abs(pointer->data - pointer->next->data);
		//add new cylinder
		//place new cylinder in the position of the old cylinder in the linkedlist
		if(arrayTraverse > 999){
			pointer->data = -10000;
		}
		//still have more to add from array
		if(arrayTraverse <= 999){
			pointer->data = cylinders[arrayTraverse];
		}
		//increment traverse
		arrayTraverse++;
		//move pointer
		pointer = pointer->next;
	}

	//yes we are at the end of the linkedList
	if(pointer->next == NULL){
		//add head movement
		fcfsHeadMovements += abs(pointer->data - start->data);
		//add new cylinder
		//place new cylinder in the position of the old cylinder in the linkedlist
		//we have gone through the full array
		if(arrayTraverse > 999){
			pointer->data = -10000;
		}
		//still have more to add from array
		if(arrayTraverse <= 999){
			pointer->data = cylinders[arrayTraverse];
		}
		//increment traverse
		arrayTraverse++;
		//move pointer
		pointer = start;
	}

	//printf("%d   " , arrayTraverse);
	//printf("%d\n",fcfsHeadMovements);
}






return(fcfsHeadMovements);





	// //move pointer
	// //normal move
	// if(pointer->next != NULL){

	// }
	// //move back to start of DoublyLinkedList
	// if(pointer->next == NULL){
	// 	pointer = start;
	// }



	//printBlue("d\n",fcfsHeadMovements);

	//delete value replace with next value from array
	//print 100 out the doubly linked list

}

// void SSTF(){
// }
// void SCAN(){
// }
// void CSCAN(){
// }
// void LOOK(){
// }
// void CLOOK(){
// }
