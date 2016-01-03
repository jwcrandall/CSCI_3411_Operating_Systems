#include "methods.h"
int clook(node *pointer, int headStart){
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
    node * max;
    node * min;
   	while(1){

	    swap = currentDirection;
	    currentDirection = directionCheck(pointer, currentDirection);

	    if(swap != currentDirection){
	    	if(swap == 0){
	    		//get to the min node go back to the max node adding needed head movments and repositioning pointer maintain direction of 0
	    		max = maxNode();
	    		headMovements += abs(pointer->data - max->data);
	    		if(arrayTraverse > 999){
	         		pointer->data = -10000;
	    		}
	    		if(arrayTraverse <= 999){
	         		pointer->data = cylinders[arrayTraverse];
	    		}
	    		arrayTraverse++;
	    		pointer = max;
	    		//headMovements += 2*(abs(pointer->data-4999));
	    		currentDirection = 0;
	    	}
	    	if(swap == 1){
	    		//get to the max node go back to the min adding needed head movments and repositioning pointer maintaining direction of 1
	    	    headMovements += 2*(abs(pointer->data-4999));
	    		min = minNode();
	    		headMovements += abs(pointer->data - max->data);
	    		if(arrayTraverse > 999){
	         		pointer->data = -10000;
	    		}
	    		if(arrayTraverse <= 999){
	         		pointer->data = cylinders[arrayTraverse];
	    		}
	    		arrayTraverse++;
	    		pointer = min;
	    		//headMovements += (abs(pointer->data-0));
	    		currentDirection = 1;
	    	}
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
  	}
}