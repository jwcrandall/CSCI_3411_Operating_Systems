/**
 * Simple shell interface program.
 *
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE		80 /* 80 chars per line, per command */


//Priority Queue Used in History Feature
//defining the structure that I am going to be using in my priorityQueue aray
// typedef struct{
//     // int id; //this is a unique integer id
//     char *args[MAX_LINE/2 + 1]  //array that holds the tokenized elements that will be stored in history
//     int priority; // this is the prioirty value
// }element;


// void insertPriorityQueueElement(element priorityQueue[], int id, int priorityValue, int arraySize){
// //check children
// //size in bites divided by the size of each indivudal element, it is in byteps, but will tell you the correct zise of elemetns becuase you are dividing by the size of one structure
//     for (int i = 0; i < arraySize; i++){
//         //goes down array untill the priority value finds the first priorty value that is is biggern then
//         if (priorityValue >= priorityQueue[i].priority)
//         {
//             //shift all elements equal to or bellow the new element in the prioirty queue up the array by one
//             for (int j = arraySize;j>i;j--)
//             {
//                 priorityQueue[j] = priorityQueue[j-1];
//             }
//             //set the function values to that locatoin
//             priorityQueue[i].priority = priorityValue;
//             priorityQueue[i].id = id;
//             return;
//         }
//     }
// }


// // this method prints out the content of each element at every index in the array
// void printPriorityQueueElementInArray(element priorityQueue[], int elementCount){
//     int i = 0;
//     if (elementCount == -1){
//         printf("\nNo Elements to print");
//         printf("\n");
//     }
//     else{
//         printf("\nElements in the priority queue printed in order of highest prioirty");
//         printf("\n");
//         for (i = 0; i <= elementCount; i++){
//             printf("\n");
//             printf("Id      : ");
//             printf("%d", priorityQueue[i].id);
//             printf("\n");
//             printf("Priority: ");
//             printf("%d", priorityQueue[i].priority);
//             printf("\n");
//         }
//     }
// }









int main(void)
{

    //char *my_string;
    size_t size;
    char *args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
    int should_run = 1;
	int i, upper;


    while (should_run)
    {



        //reading the imput string
        printf("partytime@joes1.0>");
        fflush(stdout);

        char *line [MAX_LINE] ; //this is where the string is intilized and has a pointer set to it with MAX_LINE Indexes
        size_t;
        getline(line,&size,stdin);

        //printf("%s", *line);





//replace last element in array with null
//    int size;
 //   size = strlen(*line) -1;
  //  printf("%s",*line);

//cannot reach this element, not doing what is desired

    //line[size] = NULL;





// remove the elemettn before the \0 in your array, which is a create new line aka \n
//removes it by decreaseing string by 1 \0 is always included by the c compiler



char *foo = *line;
foo[strlen(foo) - 1] = 0;
//what does foo get used

//line[strlen(line) - 1] = 0;

//char *foo = asctime();
//foo[strlen(foo) - 1] = 0;

//character in your string in c, which is an array

  //  list[2][4];

    //get rid of /n




        //check for exit
        char exit[] = "exit";
        if(strcmp(exit,*line) == 0)
        {
            return;
        }







//tokenization
//page 118
//line is the string that has been imputd
//args is the array that tokenized line is put into

        int i = 0;

//char *token;

        for (i ; i <= MAX_LINE ; i++)
        {
            args[i] = strsep(line, " " ); //question????  //strsep expects a char** as its first parameter
            //speeds up the checking of the array
            if(args[i] == NULL){
                break;
            }
        }

       // printf("array [0]");printf("%s", args[0]);
       // printf("array [1]");printf("%s", args[1]);
       // printf("array [2]");printf("%s", args[2]);
       // printf("array [3]");printf("%s", args[3]);
       // printf("array [4]");printf("%s", args[4]);



// \n

       //printf("%s", args[3]);

//print a test array in c
// char test1[20] = "Hello World";
//    printf("%s\n",test1);




//checking for the & and waiting


//history function, use your prioirty queue








//forking
    //pid_t is data type is a signed integer type which is capable of representing a process ID
        pid_t pid;
        /*fork creates a child process*/
        pid = fork();

        if(pid<0){ /* error occurred */
             fprintf(stderr, "Fork Failed");
             return 1;
        }

        //printf("%d", pid);
        if (pid == 0){

            //child process
            //execvp gets all the unix comands to fun in the shell
            int p = execvp(args[0], args);
            //printf("%d\n", p );
        }

        else{
            /* parent process*/
            /*parent will wait for the child to complete */
            wait(NULL);
           // printf("Child Complete\n");
        }

    }

	return 0;












}


// if their is an & then chekck boolean after the fork, and you have to remove it from the arguments then try
