/*
 * circularLinkedList.c
 */
#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
        int data;
        struct Node *next;
}node;


void insertAtEnd(node *pointer, int data)
{
        node *start = pointer;
        /* Iterate through the list till we encounter the last node.*/
        while(pointer->next!=start)
        {
                pointer = pointer -> next;
        }
        /* Allocate memory for the new node and put data in it.*/
        pointer->next = (node *)malloc(sizeof(node));
        pointer = pointer->next;
        pointer->data = data;
        pointer->next = start;
}



//same needs to be changed

//works!!!
void insertAtFront(node *pointer, int data)
{
    struct Node *new_node;
    /* Allocate memory for the new node and put data in it.*/
    new_node = (node *)malloc(sizeof(node));
    new_node -> data = data;

        if(pointer->next == NULL){
            pointer->next = new_node;

        }

        else{
            new_node->next = pointer->next;
            pointer->next = new_node;
        }
}



 //       node *start = pointer;
        /* Iterate through the list till we encounter the last node.*/
    //    while(pointer->next!=start)
      //  {
        //        pointer = pointer -> next;
  //      }
        /* Allocate memory for the new node and put data in it.*/
       // pointer->next = (node *)malloc(sizeof(node));
    ///    pointer = pointer->next;
  //      pointer->data = data;
//        pointer->next = start;


















int find(node *pointer, int key)
{
        node *start = pointer;
        pointer =  pointer -> next; //First node is dummy node.
        /* Iterate through the entire linked list and search for the key. */
        while(pointer!=start)
        {
                if(pointer->data == key) //key is found.
                {
                        return 1;
                }
                pointer = pointer -> next;//Search in the next node.
        }
        /*Key is not found */
        return 0;
}
void delete(node *pointer, int data)
{
        node *start = pointer;
        /* Go to the node for which the node next to it has to be deleted */
        while(pointer->next!=start && (pointer->next)->data != data)
        {
                pointer = pointer -> next;
        }
        if(pointer->next==start)
        {
                printf("Element %d is not present in the list\n",data);
                return;
        }
        /* Now pointer points to a node and the node next to it has to be removed */
        node *temp;
        temp = pointer -> next;
        /*temp points to the node which has to be removed*/
        pointer->next = temp->next;
        /*We removed the node which is next to the pointer (which is also temp) */
        free(temp);
        /* Beacuse we deleted the node, we no longer require the memory used for it .
           free() will deallocate the memory.
         */
        return;
}
void print(node *start,node *pointer)
{
        if(pointer==start)
        {
                return;
        }
        printf("%d ",pointer->data);
        print(start,pointer->next);
}

//probably will not work
// still does not count origianl
//needs work!!!!!!!!, problem with extra one
//says one when their is no value
void count(node *pointer)
{

    struct Node *start;
    int count;
    start=pointer->next;

    if(start == NULL){
    count = 0;
    }
    else{
        count = 1;
        //if(pointer->next != NULL){

    while(start->next!=pointer)
        {
            start=start->next;
            count++;
        }
    }



        printf("the number of elements in this circularLinkedList =%5d\n",count);
    //}
}



int main()
{
        /* start always points to the first node of the linked list.
           temp is used to point to the last node of the linked list.*/
        node *start,*temp;
        start = (node *)malloc(sizeof(node));
        temp = start;
        temp -> next = start;
        /* Here in this code, we take the first node as a dummy node.
           The first node does not contain data, but it used because to avoid handling special cases
           in insert and delete functions.
         */


        printf("circularLinkedList Functions\n");
        printf("1. Insert a node with integer data as the last node\n");
        printf("2. Delete all nodes containing input data\n");
        printf("3. Print\n");
        printf("4. Search for a node with input data\n");
        printf("5. Insert a node with integer data as the first node\n");
        printf("6. Count the number of nodes in the Single Link List\n");
        printf("0. Exit\n");



        //printf("1. Insert a node with integer data as the first node \n");
        //printf("2. Insert a node with integer data as the last node\n");
        //printf("3. Delete all nodes containing input data\n");
        //printf("4. Print\n");
        //printf("5. Search for a node with input data\n");

        while(1)
        {
                int query;
                scanf("%d",&query);
                if(query==1)
                {
                        int data;
                        scanf("%d",&data);
                        insertAtEnd(start,data);
                }
                else if(query==2)
                {
                        int data;
                        scanf("%d",&data);
                        delete(start,data);
                }
                else if(query==3)
                {
                        printf("The list is ");
                        print(start,start->next);
                        printf("\n");
                }
                else if(query==4)
                {
                        int data;
                        scanf("%d",&data);
                        int status = find(start,data);
                        if(status)
                        {
                                printf("Element Found\n");
                        }
                        else
                        {
                                printf("Element Not Found\n");

                        }
                }
                else if(query==5)
                {
                        int data;
                        scanf("%d",&data);
                        insertAtFront(start,data);
                }
                else if (query==6)
                {
                        count(start);
                }

                else if (query==0)
                {
                        exit(0);
                }
                else
                {
                        printf("not an accepted command");
                }
        }


}