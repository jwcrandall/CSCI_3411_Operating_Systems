#include "methods.h"


int scan(node *pointer, int headStart){
	//reset counters
    int headMovements = 0;
	int arrayTraverse = 0;
	int currentDirection;
	int swap;
    //place first 100 cylindes in linked list
	for(int i = 0 ; i < 100 ; i++){
		arrayTraverse = i;
		insertAtEnd(pointer,cylinders[arrayTraverse]);
																					//printf("%d   " , arrayTraverse);
																					//printf("%d\n", cylinders[arrayTraverse]);
	}
	node * fm = leastSeekFirstMove(headStart);
	if(fm->data - headStart <= 0){
	currentDirection = 0;
	}
	if(fm->data - headStart > 0){
	currentDirection = 1;
	}

																// printBrown("linked List Direction: ");
																// printf("%d   \n",currentDirection);


    																//node * lfm = headFirstMove(headStart, currentDirection);
	headMovements += abs(headStart - fm->data);
																	//printf("%d\n", firstHeadMovement);
																	//headMovements = firstHeadMovement;
    pointer = fm;

																	//printf("%d\n", headMovements);
																    //printf("%d   " , arrayTraverse);
																    //printf("%d\n",headMovements);


    node * scan;
    //int swap;

															    //print(start);
															    //printf("\n");

   	while(1){

   														// 	printBrown("linked List Direction: ");
																	// 	printf("%d   ",currentDirection);
															  // //   //having trouble geting out of the while loop
															  //   //while (scan->data != -10000){
																	// printCyan("Array Index: ");
																	// printf("%d   " , arrayTraverse);
																	// printBlue("pointer->data: ");
																 //    printf("%d     ", pointer->data);


															  // 		printBrown("linked List Direction: ");
																	// printf("%d   ",currentDirection);
	    swap = currentDirection;
	    currentDirection = directionCheck(pointer, currentDirection);
																	 //    printBrown("linked List Direction: ");
																		// printf("%d   ",currentDirection);
																		// // printBlue("pointer->data: ");
																	 // //    printf("%d     ", pointer->data);
	    //printGreen("nick print 1");
	    if(swap != currentDirection){
	    	if(swap == 0){
	    		headMovements += 2*(abs(pointer->data-0));
	    	}
	    	if(swap == 1){
	    		headMovements += 2*(abs(pointer->data-4999));
	    	}
	    }
	    //printGreen("nickPrint 2");

	    scan = scanMove(pointer, currentDirection);
																	    // printBlue("pointer->data: ");
																	    // printf("%d     ", pointer->data);
																	 //    printGreen("headMovements: ");
																		// printf("%d   ",headMovements);
																		 //    printRed("scan->data: ");
																			// printf("%d   ", scan->data);
			 															//print(start);

	    if(scan->data == -10000){
																	  //   	print(start);
																	  //   	printRed("scan->data: ");
																			// printf("%d   \n", scan->data);
	    	return(headMovements);
    	}

	    headMovements += abs(pointer->data - scan->data);
	    if(arrayTraverse > 999){
	         pointer->data = -10000;
	    }
	    if(arrayTraverse <= 999){
	         pointer->data = cylinders[arrayTraverse];
	    }
																		    //  printBlue("pointer->data: ");
																		    // printf("%d     \n", pointer->data);
																		    // printCyan("joe");


	    arrayTraverse++;
	    pointer = scan;
	    																	//printGreen("nicks print end");
  	}


	//return(headMovements);
}

















// we could have a structural problem
int directionCheck(node * pointer, int currentDirection){
 	node * traverseNode = start;
	if(currentDirection == 1){
		while(traverseNode->next != NULL){
	        if(abs(traverseNode->data - 4999) < abs(pointer->data - 4999)){
	        	return(1);
	        }
	    	traverseNode = traverseNode->next;
		}
		return(0);
	}
	if(currentDirection == 0){
		while(traverseNode->next != NULL){
	        if(abs(traverseNode->data - 0) < abs(pointer->data - 0)){
	        	return(0);
	        }
	        traverseNode = traverseNode->next;
		}
		return(1);
	}

																					//printRed("code should never get here");
//return(-123456789);
}








node * scanMove(node * pointer, int currentDirection){
	int difference = 999999999;
    node * scanNode;
    //moves through the linked list
    node * traverseNode = start;
    //catch all but last, need to fix							 however traverseNode != NULL gives me segmentation fault (actually both cause seg fualt)
    while(traverseNode != NULL){
    	//going left
    	if(currentDirection == 0){
    		//new cylinder is smaller than current node
			if(abs(pointer->data - traverseNode->data) < difference && pointer->data > traverseNode->data ){
            	//make sure trverse node not in the same possition as the current pointer
            	if(traverseNode != pointer){
                	difference = abs(pointer->data - traverseNode->data);
                	scanNode = traverseNode;
            	}
       		 }
       	}
    	//going right
    	if(currentDirection == 1){
    		//new cylinder is larger than current cyliner
			if(abs(pointer->data - traverseNode->data) < difference && pointer->data < traverseNode->data ){
            	//make sure trverse node not in the same possition as the current pointer
            	if(traverseNode != pointer){
                	difference = abs(pointer->data - traverseNode->data);
                	scanNode = traverseNode;
            	}
       		 }
    	}
    	//this will cause a null pointer i think
    	traverseNode = traverseNode->next;
    }
    // printBrown("scanNode->data: ");
    // printf("%d\n", scanNode->data);
    return(scanNode);
}


