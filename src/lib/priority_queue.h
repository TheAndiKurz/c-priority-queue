#pragma once

#include "heap.h"

struct PriorityQueue
{
    Heap *heap;
};
typedef struct PriorityQueue PriorityQueue;

// create, delete
PriorityQueue *priority_queue_new(int (*compare)(void *, void *));
void priority_queue_destroy(PriorityQueue *pq);

// priority queue operations
void priority_queue_push(PriorityQueue *pq, void *data);

void *priority_queue_pop(PriorityQueue *pq);

void *priority_queue_peek(PriorityQueue *pq);

size_t priority_queue_size(PriorityQueue *pq);

bool priority_queue_is_empty(PriorityQueue *pq);
