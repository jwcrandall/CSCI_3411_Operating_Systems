#include <unistd.h>
#include <stdio.h>

int main(){
    char *paramList[] = {"ls", "-l", "-a", NULL};
    execvp(paramList[0], paramList);

    printf("Will this line get printed?\n");
    return 0;
}