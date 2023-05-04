#pragma once

#include "array_list.h"
#include <stdbool.h>

struct Heap {
    ArrayList *list;
    int (*compare)(void *, void *);
};
typedef struct Heap Heap;


// create, delete
Heap *heap_new(int (*compare)(void *, void *));
void heap_destroy(Heap *heap);

// heap operations
void heap_push(Heap *heap, void *data);
void *heap_peek(Heap *heap);
void *heap_pop(Heap *heap);

size_t heap_size(Heap *heap);
bool heap_is_empty(Heap *heap);
