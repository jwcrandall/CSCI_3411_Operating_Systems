#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    int i = 0;

    if(fork() == 0){
        for(i = 0; i < 20; i++)
            printf("Child: %d\n", i);
    }else{
        wait(NULL);
        for(i = 0; i < 20; i++)
            printf("Parent: %d\n", i);
    }


    return 0;
}