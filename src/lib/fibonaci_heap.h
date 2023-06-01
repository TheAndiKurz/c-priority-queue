#pragma once

#include "array_list.h"
#include "tree.h"

struct FibonaciHeap
{
    ArrayList roots; // arraylist of Nodes
    Node *min;
    size_t size;
};
typedef struct FibonaciHeap FibonaciHeap;

FibonaciHeap *fibonaci_heap_new();
void fibonaci_heap_destroy(FibonaciHeap *heap);

// heap operations
size_t fibonaci_heap_size(FibonaciHeap *heap);
bool fibonaci_heap_is_empty(FibonaciHeap *heap);

void fibonaci_heap_push(FibonaciHeap *heap, void *value);
void *fibonaci_heap_peek(FibonaciHeap *heap);
void *fibonaci_heap_pop(FibonaciHeap *heap);
