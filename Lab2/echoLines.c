#include <stdio.h>
#define MAX_SIZE 1024

int main(){
    char *line[MAX_SIZE];
    size_t size;

    while(getline(line, &size, stdin) != -1)
        printf("%s", *line);

    return 0;
}