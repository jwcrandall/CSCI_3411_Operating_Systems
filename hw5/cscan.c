#include "methods.h"
int cscan(node *pointer, int headStart){
    int headMovements = 0;
	int arrayTraverse = 0;
	int currentDirection;
	int swap;

	for(int i = 0 ; i < 100 ; i++){
		arrayTraverse = i;
		insertAtEnd(pointer,cylinders[arrayTraverse]);
	}
	node * fm = leastSeekFirstMove(headStart);
	if(fm->data - headStart <= 0){
		currentDirection = 0;
	}
	if(fm->data - headStart > 0){
		currentDirection = 1;
	}
	headMovements += abs(headStart - fm->data);
    pointer = fm;
    node * scan;
    node * temp;
   	while(1){



		//int minnum = ismin(pointer);
		//int maxnum = ismax(pointer);
			    		    		    				    		    		    	    		    	printBlue("outside");
		if(ismin(pointer) == 1 || ismax(pointer)==1){
			printBlue("end");
			//printf("%d\n",minnum);
		    if(ismin(pointer) == 1){
		    	//get from the bottom go back to the top adding needed head movments and repositioning pointer maintain direction of 0
		    	headMovements += abs(pointer->data - 0);
		    	headMovements += 5000;
		    	if(arrayTraverse > 999){
		       		pointer->data = -10000;
		    	}
		    	if(arrayTraverse <= 999){
		       		pointer->data = cylinders[arrayTraverse];
		   		}
		    	arrayTraverse++;
		    	// //causing the segmentation fault
		    	temp = maxNode();
		    	headMovements += 2*(abs(temp->data-4999));
		    	// currentDirection = 0;


		    }
		    if(ismax(pointer)==1){
		    	//get from the top go back to the bottom adding needed head movments and repositioning pointer maintaining direction of 1
		        headMovements += 2*(abs(pointer->data-4999));
		    	headMovements += 5000;
		    	if(arrayTraverse > 999){
		       		pointer->data = -10000;
		   		}
		   		if(arrayTraverse <= 999){
		       		pointer->data = cylinders[arrayTraverse];
		    	}
		    	arrayTraverse++;
		    	temp = minNode();
		    	headMovements += (abs(pointer->data-0));
		    	currentDirection = 1;
		    }
		    pointer = temp;
		}


	    scan = scanMove(pointer, currentDirection);

	    if(scan->data == -10000){
	    	return(headMovements);
    	}

	    headMovements += abs(pointer->data - scan->data);

	    if(arrayTraverse > 999){
	         pointer->data = -10000;
	    }
	    if(arrayTraverse <= 999){
	         pointer->data = cylinders[arrayTraverse];
	    }

	    arrayTraverse++;
	    pointer = scan;



	    												// 			printBrown("linked List Direction: ");
																	// printf("%d   ",currentDirection);
															 	// 	printCyan("Array Index: ");
																	// printf("%d   " , arrayTraverse);
																	// printBlue("pointer->data: ");
																 //    printf("%d     ", pointer->data);
																 //    printRed("head headMovements");
																 //    printf("%d   \n", headMovements);


  	}
}



int ismax(node * pointer){
    node * traverseNode = start;
    while(traverseNode != NULL){
		if(traverseNode->data > pointer->data && traverseNode->data < 5000){
           	//not max
           	return(0);
        }
        traverseNode = traverseNode->next;
    }
    //is max
 	return(1);
}

int ismin(node * pointer){
   node * traverseNode = start;
    while(traverseNode != NULL){
		if(traverseNode->data < pointer->data && traverseNode->data > -1){
           	//not min
           	return(0);
        }
        traverseNode = traverseNode->next;
    }
    //is min
 	return(1);
}



node * maxNode(){
    node * maxNode;
    maxNode->data = -1;
    node * traverseNode = start;

    while(traverseNode != NULL){
		if(traverseNode->data > maxNode->data && traverseNode->data < 5000){
           	maxNode = traverseNode;
        }
        traverseNode = traverseNode->next;
    }
 	return(maxNode);
}



node * minNode(){
    node * minNode;
    node * traverseNode = start;
    while(traverseNode != NULL){
		if(traverseNode->data < minNode->data && traverseNode->data > -1){
               	minNode = traverseNode;
       	}
    	traverseNode = traverseNode->next;
    }
    return(minNode);
}

