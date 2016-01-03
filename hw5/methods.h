#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//#include "terminalColors.h"
#define CLEAR 			"\033[0m"
#define BLACK 			"\033[22;30m"
#define RED 			"\033[22;31m"
#define GREEN 			"\033[22;32m"
#define BROWN 			"\033[22;33m"
#define BLUE 			"\033[22;34m"
#define MAGENTA 		"\033[22;35m"
#define CYAN 			"\033[22;36m"
#define GRAY 			"\033[22;37m"
#define BOLD_GRAY 		"\033[01;30m"
#define BOLD_RED 		"\033[01;31m"
#define BOLD_GREEN 		"\033[01;32m"
#define YELLOW 			"\033[01;33m"
#define BOLD_BLUE 		"\033[01;34m"
#define BOLD_MAGENTA	"\033[01;35m"
#define BOLD_CYAN 		"\033[01;36m"
#define WHITE 			"\033[01;37m"

//data structures
typedef struct Node
{
        int data;
        struct Node *next;
        struct Node *prev;
}node;

//start always points to the first node of the linked list.
//temp is used to point to the last node of the linked list.
//declare two pointers to struct Node named node_t
node *start;





//initialize methods
void initialize();
long random_at_most(long max);
void print_cylinders();
//initialize global variables
int headStart;
int cylinders[1000];

//data structure methods
//void insertAtFront(node *pointer, int data);
void insertAtEnd(node *pointer, int data);
void clear();
//int find(node *pointer, int key);
//void delete(node *pointer, int data);
void print(node *pointer);

//fcfs methods
int fcfs(node *pointer, int headStart);

//sstf methods
int sstf(node *pointer, int headStart);
node * leastSeekFirstMove(int headStart);
node * leastSeek(node *pointer);

//scan methods
int scan(node *pointer, int headStart);
//node * headFirstMove(int headStart, int currentDirection);
//int firstDirectionCheck(int headStart, int currentDirection);
int directionCheck(node * pointer, int currentDirection);
node * scanMove(node * pointer, int currentDirection);

//cscan methods
int cscan(node *pointer, int headStart);
node * maxNode();
node * minNode();
int ismin(node * pointer);
int ismax(node * pointer);

//look methods
int look(node *pointer, int headStart);

//clook methods
int clook(node *pointer, int headStart);


//scheduling methods global varibales
int fcfsHeadMovements;
int fcfsRuns;

//color print
void printRed(char* chArr);
void printBlue(char* chArr);
void printGreen(char* chArr);
void printCyan(char* chArr);
void printBrown(char* chArr);







