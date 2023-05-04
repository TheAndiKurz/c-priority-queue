#include "priority_queue.h"


// create, delete
void priority_queue_init(PriorityQueue *pq, int (*compare)(void *, void *)) {
    pq->heap = heap_new(compare);
}

PriorityQueue *priority_queue_new(int (*compare)(void *, void *)) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    priority_queue_init(pq, compare);
    return pq;
}

void priority_queue_destroy(PriorityQueue *pq) {
    heap_destroy(pq->heap);
    free(pq);
}


// push, pop
void priority_queue_push(PriorityQueue *pq, void *data) {
    heap_push(pq->heap, data);
}

void *priority_queue_pop(PriorityQueue *pq) {
    return heap_pop(pq->heap);
}

void *priority_queue_peek(PriorityQueue *pq) {
    return heap_peek(pq->heap);
}

size_t priority_queue_size(PriorityQueue *pq) {
    return heap_size(pq->heap);
}

bool priority_queue_empty(PriorityQueue *pq) {
    return heap_is_empty(pq->heap);
}

