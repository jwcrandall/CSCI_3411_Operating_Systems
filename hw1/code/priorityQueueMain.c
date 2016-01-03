/*
 * priorityQueueMain.c
 */

#include <stdio.h>
#include "priorityQueue.h"
#include "priorityQueue.c"
#include "test.h"
#include "test.c"

int main(int argc, char *argv[]) {
    PQueue *q = NULL;
    Test *t = NULL;
    int i;

    srand(time(NULL));

    /* A priority Queue containing a maximum of 10 elements */
    q = pqueue_new(test_compare, 10);

    for(i = 0; i < 10; ++i) {
        /* Adding elements to priority Queue */
        t = test_new(rand());
        pqueue_enqueue(q, t);
    }

    for(i = 0; i < 10; ++i) {
         printf("%dn", ((Test*)pqueue_dequeue(q))->priority);
        /* Free memory - me lazy */
    }

    /* Free memory - me lazy */

    return (0);
}