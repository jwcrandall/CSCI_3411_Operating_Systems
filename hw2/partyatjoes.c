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


typedef struct Node
{
        char *data;
        struct Node *next;
        struct Node *prev;
}node;

// works!!!
void insertAtFront(node *pointer, char *data)
{
    struct Node *new_node;
        /* Allocate memory for the new node and put data in it.*/
        new_node = (node *)malloc(sizeof(node));
        new_node -> data = data;

    /* Check if the list is empty, is so insert new node after start.*/
    if(pointer->next == NULL)
    {
        pointer->next = new_node;
        new_node->prev = pointer;
    }
    else{
        new_node->next = pointer->next;
        (pointer->next)->prev = new_node;
        pointer->next = new_node;
        new_node->prev = pointer;
    }
}
//print out the elements in the history linked list
void print(node *pointer)
{
        if(pointer==NULL)
        {
                return;
        }
        printf("%s ",pointer->data);
        print(pointer->next);
}








int main(void)
{


    //used for history
     /* start always points to the first node of the linked list.
           temp is used to point to the last node of the linked list.*/
        node *start,*temp;
        start = (node *)malloc(sizeof(node));
        temp = start;
        temp -> next = NULL;
        temp -> prev = NULL;

    //used for tokenization
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

        //this is where the string is intilized and has a pointer set to it with MAX_LINE Indexes
        char *line [MAX_LINE] ;
        //size_t;
        getline(line,&size,stdin);

        printf("%s", *line);


        //put the character array in the history
        char *hist = *line;
        insertAtFront(start,hist);

        //remove last \n in array
        char *foo = *line;
        foo[strlen(foo) - 1] = 0;

       // char last = *line[line.length -1];

        //if(foo[strlen(foo) - 1] == "&"){
        //    printf("yes");
        //}


        printf("%s", *line);
        //special commands

        //find the last charachter in the string
        //if it is % update boolean
        // remove it from string


        //dont allow while to run if back is zero


        //char *lastChar = *line
        //*lastChar =

        //printf("%s\n",*lastChar);





        // int back = 0;
        // //check for &
        // //char &[] = "&";
        // if(strcmp("&", *line) ==0)
        // {
        //     back = 1;
        // }









       // printf(background);

        // //check for history
        // int bool historycheck = 0;
        // char history[] = "history";
        // if(strcmp(history, *line) ==0)
        // {
        //     historycheck = 1;
        // }




        //add to history



        //print history
        char his[] = "history";
        if(strcmp(his, *line) ==0)
        {
            printf("The command histo is ");
                        print(start->next);
                        printf("\n");
        }



        //exit
        printf("%s\n","cycle");
        //check for exit
        char ex[] = "exit";
        if(strcmp(ex, *line) ==0)
        {
            break;
        }



        //check for &
        char *c = *line;
        int back = 0;
        // for(k; k < strlen(*line); k++)
        // {
            if(c[strlen(c)-1] == '&')
            {
                printf("& detected saved and removed\n");
                back = 1;
                c[strlen(c)-1] = 0;
                printf("%s",*line);
            }
            // if(c[strlen(c)-1]=="\0"){
            //     c[strlen(c)-1] = 0;
            // }

        // }






        //tokenization
        //page 118
        //line is the string that has been imputd
        //args is the array that tokenized line is put into

        //int i = 0;
        for (int i =0 ; i <= MAX_LINE ; i++)
        {
            args[i] = strsep(line, " " ); //question????  //strsep expects a char** as its first parameter
            //speeds up the checking of the array
            if(args[i] == NULL){
                break;
            }
        }
        printf("array [0]");printf("%s\n", args[0]);
        printf("array [1]");printf("%s\n", args[1]);
        printf("array [2]");printf("%s\n", args[2]);
        printf("array [3]");printf("%s\n", args[3]);
        printf("array [4]");printf("%s\n", args[4]);
        printf("array [5]");printf("%s\n", args[5]);
        printf("array [6]");printf("%s\n", args[6]);

        //print array in c




        //find last elment in array in c

       // printf("%s\n", [args lastObject]);




        //for(int h = 0; h < 3; h++) {
        //        printf("%s ", args[h]);
        //    printf("\n");
       // }








        //forking
        //pid_t is data type is a signed integer type which is capable of representing a process ID
        pid_t pid;
        /*fork creates a child process*/
        pid = fork();

        if(pid<0)
        { /* error occurred */
            fprintf(stderr, "Fork Failed");
                return 1;
        }

        if (pid == 0)
        {
        //child process
        //execvp gets all the unix comands to fun in the shell
        int p = execvp(args[0], args);
        return (0);
        }

        //check with nich

        //while
        //{

        if(back != 1)
        {
            wait(NULL);
        }

        // if (back != 1 ){
        //     int * status;
        //     do{
        //         wait(status);
        //     }
        //     while(!WIFEXITED(status));
        // }



       // else{
        /* parent process*/
        /*parent will wait for the child to complete */


    }
	return 0;
}