#include "methods.h"
int look(node *pointer, int headStart){
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
   	while(1){
	    swap = currentDirection;
	    currentDirection = directionCheck(pointer, currentDirection);
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
  	}
}