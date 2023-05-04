#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "heap.h"

int compare(void *a, void *b) {
    return (long)a - (long)b;
}


int main(void)
{
    srand(time(NULL));
    Heap *heap = heap_new(compare);

    for (long i = 0; i < 1000; i++) {
        long r = rand() % 1000;
        heap_push(heap, (void *) r);
    }
    
    for (long i = 0; i < 1000; i++) {
        printf("%ld\n", (long)heap_pop(heap));
    }

    heap_destroy(heap);
    return 0;
}