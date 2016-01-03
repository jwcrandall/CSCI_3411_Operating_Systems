#include <stdio.h>
#include <stdlib.h>


//defining the structure that I am going to be using in my priorityQueue aray
 typedef struct{
        int id; //this is a unique integer id
        int priority; // this is the prioirty value, does not need to be unique
    }element;



void insertPriorityQueueElement(element priorityQueue[], int id, int priorityValue, int arraySize){

//check children
//size in bites divided by the size of each indivudal element, it is in byteps, but will tell you the correct zise of elemetns becuase you are dividing by the size of one structure

    for (int i = 0; i < arraySize; i++){

        //goes down array untill the priority value finds the first priorty value that is is biggern then
        if (priorityValue >= priorityQueue[i].priority){

            //save the old priroty value and data
           // int tempPriority = priorityQueue[i].priority;
         //   int tempId = prirotyQueue[i].data;



            //shift all elements equal to or bellow the new element in the prioirty queue up the array by one
            for (int j = arraySize;j>i;j--){
            priorityQueue[j] = priorityQueue[j-1];
            }

            //set the function values to that locatoin
            priorityQueue[i].priority = priorityValue;
            priorityQueue[i].id = id;

            return;
        }
    }



}

void incrasePriorityOfAnElementInArray(element priorityQueue[], int id, int increase, int arraySize){
    int tempId;
    int tempPriority;
    for (int i = 0; i < arraySize; i++){
        //checks if the elemetn with that id is available in the array
        if(id == priorityQueue[i].id){
            tempId = id;
            tempPriority = priorityQueue[i].priority + increase;




            //shift all elements with priority less then then value bellow the new element in the prioirty queue up the down by one
            //might not work
            for (int j = arraySize;j>i;j--){
                priorityQueue[j] = priorityQueue[j+1];
            }


            //then reinsert the element with the updated priority




            //from now on it is just like insert but with differnt int k and z and temPriority
/*




            //declare another int to go throguth teh
            for (int k = 0; k < arraySize; k++){

                //goes down array untill the priority value finds the first priorty value that is is biggern then
                if (tempPriority >= priorityQueue[k].priority){

                //save the old priroty value and data
                //int tempPriority = priorityQueue[i].priority;
                //int tempId = prirotyQueue[i].data;

                //shift all elements equal to or bellow the new element in the prioirty queue up the array by one
                for (int z = arraySize;z>k;z--){
                    priorityQueue[z] = priorityQueue[z-1];
                }

                //set the function values to that locatoin
                priorityQueue[k].priority = temPriority;
                priorityQueue[k].id = tempId;

                return;

*/
        }
        else {
            printf("%d", id);
            printf(" does not exist");
            return;
        }
    insertPriorityQueueElement(priorityQueue,tempId,tempPriority,arraySize);
    }
}







//"%d", print as a decimal number
//"%c", print character
//

void extractMax(element priorityQueue[]){

printf("\nThis is the id with the highest priority : ");
printf("%d", priorityQueue[0].id);
printf("\n");
printf("This is the the highest prioirty in the prioirty queue : ");
printf("%d", priorityQueue[0].priority);

}






// this method prints out the content of each element at every index in the array
void printPriorityQueueElementInArray(element priorityQueue[], int elementCount){
    int i = 0;
    if (elementCount == -1){
        printf("\nNo Elements to print");
        printf("\n");


    }
    else{
        printf("\nElements in the priority queue printed in order of highest prioirty");
        printf("\n");
        for (i = 0; i <= elementCount; i++){
            printf("\n");
            printf("Id      : ");
            printf("%d", priorityQueue[i].id);
            printf("\n");
            printf("Priority: ");
            printf("%d", priorityQueue[i].priority);
            printf("\n");
        }
    }


}
















void changePriorityOfAnElementInArray(element priorityQueue[], int id, int change, int arraySize){
    int i;
    int j;
    int tempId;
    int tempPriority;

    for (i = 0; i < arraySize; i++){
        //checks if the element with that id is available in the array
        if(id == priorityQueue[i].id){
            tempId = id;
            tempPriority = change;
        }
    }


    //shift all elements with priority less then then value bellow the new element in the prioirty queue up the down by one
    for (j = arraySize;j>=i;j--){
        priorityQueue[j] = priorityQueue[j+1];
    }


    //insert the element with id and new priority
    insertPriorityQueueElement(priorityQueue,tempId,tempPriority,arraySize);




            //from now on it is just like insert but with differnt int k and z and temPriority
/*




            //declare another int to go throguth teh
            for (int k = 0; k < arraySize; k++){

                //goes down array untill the priority value finds the first priorty value that is is biggern then
                if (tempPriority >= priorityQueue[k].priority){

                //save the old priroty value and data
                //int tempPriority = priorityQueue[i].priority;
                //int tempId = prirotyQueue[i].data;

                //shift all elements equal to or bellow the new element in the prioirty queue up the array by one
                for (int z = arraySize;z>k;z--){
                    priorityQueue[z] = priorityQueue[z-1];
                }

                //set the function values to that locatoin
                priorityQueue[k].priority = temPriority;
                priorityQueue[k].id = tempId;

                return;

*/
}




  //  }
//    else {
  //      printf("%d", id);
    //    printf(" does not exist");
    //}
    //return;
//}














int main()
{


    // element is data type, created at the top of page
    // as opose to common datatype like int
    element priorityQueue[100];
    int elementCount = -1;

    printf("\nThis Priority Queue is implemented with single array that stores a typedef struct called Element.");
    printf("\nElement has two integer values, the id and the priority.");
    printf("\nSome functions require you to enter both id and priority.");
    printf("\nIm afraid this is not the Usane Bolt of Prioirty Queues, many shifts ahead...");
    printf("\nThe array has a max index of 100.");
    printf("\n");
    printf("\n Priority Queue Functions");
    printf("\n");
    printf("\n1 - Insert an element into PriorityQueue");
    //printf("\n2 - Delete an element from PriorityQueue");
    printf("\n2 - Print priority queue elements");
    printf("\n3 - Print the Data and Priority at the highest priority in the Prioirty Queue (AKA extractMax)");
    printf("\n4 - Incrase the priority of an Element");
    printf("\n5 - Change the prioirty of and Element");
    printf("\n6 - Exit");


    //this finds the number of elements in the array by dividing the size of the bits by the size of
    //sizeof(priorityQueue)/sizeof(priorityQueue[0])



    //trying to get elementcount to pass abck information so that you would not have to see those iritating extra itesm in


        while (1)
        {
        int ch;
        printf("\nEnter function number : ");
        scanf("%d", &ch);
        int id;
        int priority;
        int increase;
        int change;



        switch (ch)
        {
        case 1:
            printf("\nEnter the integer id for the element to be inserted : ");
            scanf("%d",&id);
            printf("\nEnter the integer priority for the element to be inserted : ");
            scanf("%d",&priority);
            insertPriorityQueueElement(priorityQueue, id,priority,sizeof(priorityQueue)/sizeof(priorityQueue[0]));
            elementCount++;
            printf("%d\n", elementCount);
            break;

        //case 2:
          //  break;

        case 2:
            printPriorityQueueElementInArray(priorityQueue,elementCount);
            break;


        case 3:

            extractMax(priorityQueue);
            break;


        case 4:
            printf("\nEnter the unique id for the element whos priority you want to incrase : ");
            scanf("%d",&id);
            printf("\nEnter the priority value for the unique data element whos priority you want to !INCRASE! : ");
            scanf("%d",&increase);
            incrasePriorityOfAnElementInArray(priorityQueue,id,increase,sizeof(priorityQueue)/sizeof(priorityQueue[0]));
          //  elementCount++;
            break;


        case 5:
            printf("\nEnter the unique id for the element whos priority you want to change : ");
            scanf("%d",&id);
            printf("\nEnter the priority value for the unique data element whos priority you want to !CHANGE! : ");
            scanf("%d",&change);
            changePriorityOfAnElementInArray(priorityQueue,id,change,sizeof(priorityQueue)/sizeof(priorityQueue[0]));
            break;

        case 0:
            exit(0);

        }
    }

}




//priorityQueue[0] = the root
//priorityQueue[1] = left child of root
//priorityQueue[2] = right child of root


//structure of this program so that it compiles


//explain this line
//A[i][j] (priority of A[i]) >= max(A[2*i+2][1])


//mcwhat is max






































































