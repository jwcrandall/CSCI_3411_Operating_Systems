#include "methods.h"

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


void printRed(char* chArr){
	printf("%s%s%s",RED,chArr, CLEAR);
}
void printBlue(char* chArr){
	printf("%s%s%s",BLUE,chArr, CLEAR);
}
void printGreen(char* chArr){
	printf("%s%s%s",GREEN,chArr, CLEAR);
}
void printCyan(char* chArr){
	printf("%s%s%s",CYAN,chArr, CLEAR);
}
void printBrown(char* chArr){
	printf("%s%s%s",BROWN,chArr, CLEAR);
}