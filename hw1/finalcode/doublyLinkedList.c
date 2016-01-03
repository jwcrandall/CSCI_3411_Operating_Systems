/*
 * doublyLinkedList.c
 */
#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
        int data;
        struct Node *next;
        struct Node *prev;
}node;

// works!!!
void insertAtFront(node *pointer, int data)
{
    struct Node *new_node;
        /* Allocate memory for the new node and put data in it.*/
        new_node = (node *)malloc(sizeof(node));
        new_node -> data = data;

    /* Check if the list is empty, is so insert new node after start.*/
    if(pointer->next == NULL){
        //pointer->next set equal to new_node
        pointer->next = new_node;
        //new_node->prev set equal to pointer
        new_node->prev = pointer;
    }
    else{
        /*everything in blue is the wrong way,
        whenver you are confused study these for lines.
        */
        new_node->next = pointer->next;
        (pointer->next)->prev = new_node;
        pointer->next = new_node;
        new_node->prev = pointer;

        //new_node = (pointer->next)->prev;
        //new_node = pointer->next;
        //new_node->prev = pointer;

        //(pointer->next)->prev = new_node;

       //4


        //newNode->NEXT = HEAD->FIRST

//HEAD->FIRST->PREV = newNode

//HEAD->FIRST = newNode

//newNode->PREV = NULL


//        pointer = new_node->prev;
  //      new_node = pointer->next;
//this is the part that fuck with me
    //    pointer->next= new_node->next;



/*

        //6






        //set the new_node pointer to the origianl pointer->next
        new_node = pointer->next;
        //set pointer to new_node previouse (prev)
        new_node->prev = pointer;
        //set the new_node to pointer->next
        pointer->next = new_node;
        //set the
        (new_node->next)->prev = new_

*/

    }

        /* Iterate through the list till we encounter the last node.
        while(pointer->next!=NULL)
        {
                pointer = pointer -> next;
        }
        Allocate memory for the new node and put data in it.
        pointer->next = (node *)malloc(sizeof(node));
        (pointer->next)->prev = pointer;
        pointer = pointer->next;
        pointer->data = data;
        pointer->next = NULL;

        */
}

void insertAtEnd(node *pointer, int data)
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
        pointer->next = NULL;
}
int find(node *pointer, int key)
{
        pointer =  pointer -> next; //First node is dummy node.
        /* Iterate through the entire linked list and search for the key. */
        while(pointer!=NULL)
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
        /* Go to the node for which the node next to it has to be deleted */
        while(pointer->next!=NULL && (pointer->next)->data != data)
        {
                pointer = pointer -> next;
        }
        if(pointer->next==NULL)
        {
                printf("Element %d is not present in the list\n",data);
                return;
        }
        /* Now pointer points to a node and the node next to it has to be removed */
        node *temp;
        temp = pointer -> next;
        /*temp points to the node which has to be removed*/
        pointer->next = temp->next;
        temp->prev =  pointer;
        /*We removed the node which is next to the pointer (which is also temp) */
        free(temp);
        /* Beacuse we deleted the node, we no longer require the memory used for it .
           free() will deallocate the memory.
         */
        return;
}
void print(node *pointer)
{
        if(pointer==NULL)
        {
                return;
        }
        printf("%d ",pointer->data);
        print(pointer->next);
}


//fix it
void count(node*pointer)
{
        int count = 0;
        node* current = pointer->next;
        while(current != NULL)
        {
                count++;
                current = current->next;
        }
        printf("the number of elements in this Doubly Link List =%5d\n",count);
}



int main()
{
        /* start always points to the first node of the linked list.
           temp is used to point to the last node of the linked list.*/
        node *start,*temp;
        start = (node *)malloc(sizeof(node));
        temp = start;
        temp -> next = NULL;
        temp -> prev = NULL;
        /* Here in this code, we take the first node as a dummy node.
           The first node does not contain data, but it used because to avoid handling special cases
           in insert and delete functions.
         */



        printf("DoubleLinkList Functions\n");


        printf("1. Insert a node with integer data as the last node\n");
        printf("2. Delete all nodes containing input data\n");
        printf("3. Print\n");
        printf("4. Search for a node with input data\n");

        printf("5. Insert a node with integer data as the first node \n");

        printf("6. Count the number of nodes in the DoubleLinkList Link List\n");

        printf("0. Exit\n");
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
                        print(start->next);
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
                else if (query==6){
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
