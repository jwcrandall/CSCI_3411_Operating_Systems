/*
 * binarySearchTree.c
 */
#include<stdio.h>
#include<stdlib.h>

typedef struct treeNode
{
        int data;
        struct treeNode *left;
        struct treeNode *right;

}treeNode;

treeNode* FindMin(treeNode *node)
{
        if(node==NULL)
        {
                /* There is no element in the tree */
                return NULL;
        }
        if(node->left) /* Go to the left sub tree to find the min element */
                return FindMin(node->left);
        else
                return node;
}

treeNode* FindMax(treeNode *node){

        if(node==NULL)
        {
                /* There is no element in the tree */
                return NULL;
        }
        if(node->right){ /* Go to the left sub tree to find the min element */
                FindMax(node->right);
            }
        else{
                return node;
        }
}

treeNode * Insert(treeNode *node,int data)
{
        if(node==NULL)
        {
                treeNode *temp;
                temp = (treeNode *)malloc(sizeof(treeNode));
                temp -> data = data;
                temp -> left = temp -> right = NULL;
                return temp;
        }

        if(data >(node->data))
        {
                node->right = Insert(node->right,data);
        }
        else if(data < (node->data))
        {
                node->left = Insert(node->left,data);
        }
        /* Else there is nothing to do as the data is already in the tree. */
        return node;

}

treeNode * Delete(treeNode *node, int data)
{
        treeNode *temp;
        if(node==NULL)
        {
                printf("Element Not Found");
        }
        else if(data < node->data)
        {
                node->left = Delete(node->left, data);
        }
        else if(data > node->data)
        {
                node->right = Delete(node->right, data);
        }
        else
        {
                /* Now We can delete this node and replace with either minimum element
                   in the right sub tree or maximum element in the left subtree */
                if(node->right && node->left)
                {
                        /* Here we will replace with minimum element in the right sub tree */
                        temp = FindMin(node->right);
                        node -> data = temp->data;
                        /* As we replaced it with some other node, we have to delete that node */
                        node -> right = Delete(node->right,temp->data);
                }
                else
                {
                        /* If there is only one or zero children then we can directly
                           remove it from the tree and connect its parent to its child */
                        temp = node;
                        if(node->left == NULL)
                                node = node->right;
                        else if(node->right == NULL)
                                node = node->left;
                        free(temp); /* temp is longer required */
                }
        }
        return node;

}

treeNode * Find(treeNode *node, int data)
{
        if(node==NULL)
        {
                /* Element is not found */
                return NULL;
        }
        if(data > node->data)
        {
                /* Search in the right sub tree. */
                return Find(node->right,data);
        }
        else if(data < node->data)
        {
                /* Search in the left sub tree. */
                return Find(node->left,data);
        }
        else
        {
                /* Element Found */
                return node;
        }
}

void PrintInorder(treeNode *node)
{
        if(node==NULL)
        {
                return;
        }
        PrintInorder(node->left);
        printf("%d ",node->data);
        PrintInorder(node->right);
}

void PrintPreorder(treeNode *node)
{
        if(node==NULL)
        {
                return;
        }
        printf("%d ",node->data);
        PrintPreorder(node->left);
        PrintPreorder(node->right);
}

void PrintPostorder(treeNode *node)
{
        if(node==NULL)
        {
                return;
        }
        PrintPostorder(node->left);
        PrintPostorder(node->right);
        printf("%d ",node->data);
}

int Count(treeNode* node){
	int c = 1;
	if(node==NULL)
	{
		return 0;
	}
	else
	{
		c += Count(node->left);
		c += Count(node->right);
		return c;
	}

}



int main()
{
//remind myself to clean up code
	 treeNode *root = NULL;

		root = Insert(root, 51);
        root = Insert(root, -143);
        root = Insert(root, 3);
        root = Insert(root, -4514);
        root = Insert(root, -4538);
        root = Insert(root, 10);
        root = Insert(root, 675);
        root = Insert(root, 555);

    printf("binarySearchTreeFunctions\n");

    printf("1. Insert a node with an input integer\n");
    printf("2. Delete a node with an input integer\n");
    printf("3. Search for a node with an imput integer\n");
    printf("4. Count the number of nodes in binarySearchTree\n");
    printf("5. Print the binarySearchTree\n");

    printf("0. Exit. \n");



while(1)
        {
                int query;
                scanf("%d",&query);

                if(query==1)
                {
                        int data;
                        scanf("%d",&data);
                        Insert(root,data);
                }
                else if(query==2)
                {
                        int data;
                        scanf("%d",&data);
                        Delete(root,data);
                }

                else if(query==3)
                {
                		treeNode* temp;
                        int data;
                        scanf("%d",&data);
			            temp = Find(root,data);
			        	if(temp==NULL)
			        	{
			               	printf("Element not found\n");
			        	}
			       		else
			       		{
			               	printf("Element Found\n");
			       		}


			                }
                else if(query==4){
                		int c = Count(root);
                        printf("\nNumber of Nodes in the binarySearchTree:%d\n ",c);

                }
                else if(query==5)
                {
                        printf("The binarySearchTree is ");
                        PrintInorder(root);
                        printf("\n");
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









