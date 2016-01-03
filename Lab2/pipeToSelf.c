#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 1024
#define READ_SIDE 0
#define WRITE_SIDE 1

int main(){
    int myPipe[2];
    int bytesRead;
    char buffer[BUF_SIZE];
    char *data = "Hello World!";

    pipe(myPipe); //Create a one-directional pipe with file descriptors stored in myPipe

    write(myPipe[WRITE_SIDE], data, strlen(data));

    if((bytesRead = read(myPipe[READ_SIDE], buffer, BUF_SIZE-2)) >= 0){
        buffer[bytesRead] = 0;  //Insert null-terminator
        printf("Read: %s\n", buffer);
    }

    return 0;
}