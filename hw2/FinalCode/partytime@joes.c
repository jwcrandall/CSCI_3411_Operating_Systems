/**
 * partytime@joes shell interface program.
 *
 * Last Modifed September 18th 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE        80 /* 80 chars per line, per command */

typedef struct Node
{
        char *data;
        struct Node *next;
        struct Node *prev;
        int commandNumber;
}node;

void insertAtEnd(node *pointer, char *data, int commandNumber)
{
        /* Iterate through the list till we encounter the last node.*/
        while(pointer->next!=NULL)
        {
                pointer = pointer -> next;
        }
        /* Allocate memory for the new node and put data in it.*/
        pointer->next = (node *)malloc(sizeof(node));
        (pointer->next)->prev = pointer;
        pointer = pointer->next;
        pointer->data = data;
        pointer->commandNumber = commandNumber;
        pointer->next = NULL;
}

//return the data at
char* getCommand(node *pointer, int key)
{
        pointer =  pointer -> next; //First node is dummy node.
        /* Iterate through the entire linked list and search for the key. */
        while(pointer!=NULL)
        {
                if(pointer->commandNumber == key) //key is found.
                {
                        return(pointer->data); // will not work
                }
                pointer = pointer -> next;//Search in the next node.
        }
        /*Key is not found */
        return 0;
}

//print out the elements in the history linked list
void print(node *pointer)
{
        if(pointer==NULL)
        {
                return;
        }
        printf("\n");
        printf("    %d",pointer->commandNumber);
        printf("    %s",pointer->data);
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

        int cn = 0;

    //used for tokenization
    //char *my_string;
    size_t size = 0;
    char *args[MAX_LINE/2 + 1]; /* command line (of 80) has max of 40 arguments */
    int should_run = 1;
    int i, upper;


    while (should_run)
    {

        //reading the imput string
        printf("partytime@joes1.0>");
        fflush(stdout);

        //this is where the string is intilized and has a pointer set to it with MAX_LINE Indexes
        char *line = NULL;
        //size_t;
        getline(&line,&size,stdin);

        //printf("%s", line);



//inserting
        //remove the \n from the end of the string
        line[strlen(line) - 1] = 0;
        // insert the command and command number into the history (linked List)
        //set a copy to be placed into the history
        char *copy = malloc(MAX_LINE * 1); //this is a char single star
        copy = strcpy(copy, line);
        //increament the comand number by 1
        cn++;
        insertAtEnd(start,copy,cn);










        //!! run previous command
        char lastcommand[] = "!!";
        if(strcmp(lastcommand, line)==0)
        {
            //get pointer to the command, check cn-1 because cn is filled by !!
            line = getCommand(start, cn-1);
        }

        //!n run n command


        if(line[0] == '!'){

            //size_t NumberOfElements = sizeof(line)/sizeof(line[0]); // determined by size of bytes and used to calcualte the number of elements
            int NumberOfElements = strlen(line);
            //printf("%s\n",line);
            //size_t NumberOfElements = sizeof(line)/sizeof(line[0]); // determined by size of bytes and used to calcualte the number of elements
            //printf("%d\n", NumberOfElements);
            char commandNumber[NumberOfElements]; // initilize array with the correct size
            commandNumber[NumberOfElements-1] = '\0'; // set the last item equal to the break
            //printf("%c\n",commandNumber[0]);

            //printf("%s\n",commandNumber); //string " "

            int test = strlen(commandNumber);
            //printf("%d\n", test);

            for (int i = 1; i < NumberOfElements; i++ ){
                if(isdigit(line[i])){
                    commandNumber[i-1]=line[i];
                    //printf("%c\n",commandNumber[i]);
                    //printf("%s\n","success");
                }
                if(isalpha(line[i])){// check if any of the imput is a character, if it is, this is invalid
                        //goto BreakExclamationChecking;

                }
            }
            //commandNumber[NumberOfElements] = '\0'; //character ' '
            //lsprintf("%s\n",commandNumber); //string " "
                int comnum;
                comnum = atoi(commandNumber); //changing command number string into command number integer
                line = getCommand(start, comnum); // get the string at that command and then your good to go
        }

         // this is where you go if the command !n was invalid

        //print history
        char his[] = "history";
        if(strcmp(his, line) ==0)
        {
            print(start->next);
            printf("\n");
            continue; //this directs back to the top of the while loop
        }


        //exit
        char ex[] = "exit";
        if(strcmp(ex, line) ==0)
        {
            break;
        }

        //check for &
        int back = 0;
        if(line[strlen(line)-1] == '&')
        {
        printf("& detected, binary fliped, and & removed\n");
        back = 1;
        line[strlen(line)-1] = '\0';
        //printf("%s",line);
        }

        //tokenization
        for (int i =0 ; i <= MAX_LINE ; i++)
        {
            args[i] = strsep(&line, " \n" ); //strsep expects a char** as its first parameter
            //speeds up the checking of the array
            if(args[i] == NULL || args[i] == '\0'){ // \0 terminating character, no notion of a string length
                args[i] = NULL;
                break;
            }
        }

        //forking
        //pid_t is data type is a signed integer type which is capable of representing a process ID
        pid_t childPid; // the hild process that the execution will soon run inside of
        /*fork creates a child process*/
        childPid = fork();
        if (childPid == 0) // fork succeeded
        {
            //execvp gets all the unix comands to run in the shell
            int p = execvp(args[0], args);
            printf("%s\n","Invalid comand");
            return (0);
        }
        if(childPid<0) // fork failed
        {
            fprintf(stderr, "Fork Failed");
            return 1;
        }
        else{
            if(back == 0)
            {

               int returnStatus;
               do
               {
                    waitpid(childPid, &returnStatus, 0);  // Parent process waits here for child to terminate.
               }
               while(!WIFEXITED(returnStatus) && !WIFSIGNALED(returnStatus));
            }
            else{
                printf("%d\n",childPid );
            }
       }
    }
    return 0;
}
