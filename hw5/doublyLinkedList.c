//doublyLinkedList
#include "methods.h"

void insertAtEnd(node *pointer, int data)
{
        if(pointer->data == -1){
            pointer->data = data;
            //printf("test\n");
            return;
        }
        /* Iterate through the list till we encounter the last node.*/
        while(pointer->next!=NULL)
        {
                //printf("test\n");
                pointer = pointer -> next;
        }
        /* Allocate memory for the new node and put data in it.*/
        pointer->next = (node *)malloc(sizeof(node));
        (pointer->next)->prev = pointer;
        pointer = pointer->next;
        pointer->data = data;
        pointer->next = NULL;
}
void clear(){
    start->next = NULL;
    start->prev = NULL;
    start->data = -1;
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
// void insertAtFront(node *pointer, int data)
// {
//     struct Node *new_node;
//         /* Allocate memory for the new node and put data in it.*/
//         new_node = (node *)malloc(sizeof(node));
//         new_node -> data = data;
//     /* Check if the list is empty, is so insert new node after start.*/
//     if(pointer->next == NULL){
//         //pointer->next set equal to new_node
//         pointer->next = new_node;
//         //new_node->prev set equal to pointer
//         new_node->prev = pointer;
//     }
//     else{
//         /*everything in blue is the wrong way,
//         whenver you are confused study these for lines.
//         */
//         new_node->next = pointer->next;
//         (pointer->next)->prev = new_node;
//         pointer->next = new_node;
//         new_node->prev = pointer;
//     }
// }
// int find(node *pointer, int key)
// {
//         pointer =  pointer -> next; //First node is dummy node.
//         /* Iterate through the entire linked list and search for the key. */
//         while(pointer!=NULL)
//         {
//                 if(pointer->data == key) //key is found.
//                 {
//                         return 1;
//                 }
//                 pointer = pointer -> next;//Search in the next node.
//         }
//         /*Key is not found */
//         return 0;
// }



// void delete(node *pointer, int data)
// {
//         /* Go to the node for which the node next to it has to be deleted */
//         while(pointer->next!=NULL && (pointer->next)->data != data)
//         {
//                 pointer = pointer -> next;
//         }
//         if(pointer->next==NULL)
//         {
//                 printf("Element %d is not present in the list\n",data);
//                 return;
//         }
//         /* Now pointer points to a node and the node next to it has to be removed */
//         node *temp;
//         temp = pointer -> next;
//         /*temp points to the node which has to be removed*/
//         pointer->next = temp->next;
//         temp->prev =  pointer;
//         /*We removed the node which is next to the pointer (which is also temp) */
//         free(temp);
//         /* Beacuse we deleted the node, we no longer require the memory used for it .
//            free() will deallocate the memory.
//          */
//         return;
// }
