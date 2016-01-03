#include "methods.h"

int sstf(node *pointer, int headStart){
	//reset counters and LinkedList
    //void clear();
    int headMovements = 0;
	int arrayTraverse = 0;

    //printRed("inside sstf\n");

    //place first 100 cylindes in linked list
	for(int i = 0 ; i < 100 ; i++){
		arrayTraverse = i;
		insertAtEnd(pointer,cylinders[arrayTraverse]);
		//printf("%d   " , arrayTraverse);
		//printf("%d\n", cylinders[arrayTraverse]);
	}
    //print(pointer);
    //printf("\n\n");


	//first move
	//smallest absolute value to the current head
    node * ls = leastSeekFirstMove(headStart);
	int firstHeadMovement = abs(headStart - ls->data);
	//printf("%d\n", firstHeadMovement);
	headMovements = firstHeadMovement ;
    pointer = ls;
	//printf("%d\n", headMovements);

    //printf("%d   " , arrayTraverse);
    //printf("%d\n",headMovements);




    //following moves
    //pointer->data != -10000
    while (1){
    ls = leastSeek(pointer);

    if(ls->data == -10000){
            // print(start);
            // printRed("scan->data: ");
            // printf("%d   \n", scan->data);
            return(headMovements);
    }

     //are we at the end of the linked list
     //if(pointer->next != NULL){
         //add head movement
         headMovements += abs(pointer->data - ls->data);
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
         pointer = ls;
    // }

     // //yes we are at the end of the linkedList
     // if(pointer->next == NULL){
     //     //add head movement
     //     fcfsHeadMovements += abs(pointer->data - start->data);
     //     //add new cylinder
     //     //place new cylinder in the position of the old cylinder in the linkedlist
     //     //we have gone through the full array
     //     if(arrayTraverse > 999){
     //         pointer->data = -1;
     //     }
     //     //still have more to add from array
     //     if(arrayTraverse <= 999){
     //         pointer->data = cylinders[arrayTraverse];
     //     }
     //     //increment traverse
     //     arrayTraverse++;
     //     //move pointer
     //     pointer = start;
     // }

     //printf("%d   " , arrayTraverse);
     //printf("%d\n",headMovements);
    }//return(headMovements);
}


node * leastSeekFirstMove(int headStart){
    int difference = 999999999;
    //node * originalNode = pointer;
    node * leastSeekNode;
    //moves through the linked list
    node * traverseNode = start;
    //catch all but last
    while(traverseNode->next != NULL){
        if(abs(headStart - traverseNode->data) < difference){
                difference = abs(headStart - traverseNode->data);
                leastSeekNode = traverseNode;
        }traverseNode = traverseNode->next;
    }return(leastSeekNode);
}



//find the value leastSeek Value to the imput value
node * leastSeek(node *pointer){
    int difference = 999999999;
    //node * originalNode = pointer;
    node * leastSeekNode;
    //moves through the linked list
    node * traverseNode = start;
    //catch all but last
    while(traverseNode->next != NULL){
        if(abs(pointer->data - traverseNode->data) < difference){
            //make sure trverse node not in the same possition as the current pointer
            if(traverseNode != pointer){
                difference = abs(pointer->data - traverseNode->data);
                leastSeekNode = traverseNode;
            }
        }traverseNode = traverseNode->next;
    }return(leastSeekNode);
}

//just passed, now you need to use it in sstf







