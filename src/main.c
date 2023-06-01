#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lib/priority_queue.h"

#define SIZE 1024

struct Notification {
    int priority;
    char *message;
};
typedef struct Notification Notification;


int compare_notifications(void *a, void *b) {
    Notification *n1 = (Notification *) a;
    Notification *n2 = (Notification *) b;
    return n1->priority - n2->priority;
}


int main(void)
{
    srand(time(NULL));
    PriorityQueue *heap = priority_queue_new(compare_notifications);

    for (long i = 0; i < SIZE; i++) {
        long priority = rand() % 10;
        Notification *r = (Notification *) malloc(sizeof(Notification));
        r->priority = priority;
        r->message = malloc(100 * sizeof(char));

        sprintf(r->message, "Notification %ld", i);

        priority_queue_push(heap, (void *) r);
    }
    
    while (!priority_queue_is_empty(heap)) {
        Notification *r = (Notification *) priority_queue_pop(heap);

        printf("Priority: %d, Message: %s\n", r->priority, r->message);

        free(r->message);
        free(r);
    }

    priority_queue_destroy(heap);
    return 0;
}
