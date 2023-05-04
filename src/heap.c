#include "heap.h"

// init, delete
void heap_init(Heap *heap, int (*compare)(void *, void *)) {
    heap->list = array_list_new();
    heap->compare = compare;
}

Heap *heap_new(int (*compare)(void *, void *)) {
    Heap *heap = malloc(sizeof(Heap));
    heap_init(heap, compare);
    return heap;
}

void heap_destroy(Heap *heap) {
    array_list_destroy(heap->list);
    free(heap);
}

// heap operations
void heapify(Heap *heap) {
    ArrayList *list = heap->list;

    size_t index = 0;
    while (index < array_list_len(list)) {
        size_t left = index * 2 + 1;
        size_t right = index * 2 + 2;
        if (left >= array_list_len(list)) {
            break;
        }

        // get the bigger child
        size_t max = left;
        if (right < array_list_len(list) && heap->compare(array_list_get(list, right), array_list_get(list, left)) > 0) {
            max = right;
        }

        // swap if the child is bigger
        if (heap->compare(array_list_get(list, index), array_list_get(list, max)) < 0) {
            void *temp = array_list_get(list, index);
            array_list_set(list, index, array_list_get(list, max));
            array_list_set(list, max, temp);
            index = max;
        } else {
            // if not bigger then you finished heapifying
            break;
        }
    }
}


void heap_push(Heap *heap, void *data) {
    ArrayList *list = heap->list;

    array_list_add(list, data);
    size_t index = array_list_len(list) - 1;
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (heap->compare(array_list_get(list, index), array_list_get(list, parent)) > 0) {
            void *temp = array_list_get(list, index);
            array_list_set(list, index, array_list_get(list, parent));
            array_list_set(list, parent, temp);
            index = parent;
        } else {
            break;
        }
    }
}

void *heap_peek(Heap *heap) {
    return array_list_get(heap->list, 0);
}

void *heap_pop(Heap *heap) {
    ArrayList *list = heap->list;

    void *value = array_list_get(list, 0);

    // set the first element to the last element
    array_list_set(list, 0, array_list_remove(list, array_list_len(list) - 1));
    
    heapify(heap);

    return value;
}

size_t heap_size(Heap *heap) {
    return array_list_len(heap->list);
}

bool heap_is_empty(Heap *heap) {
    return heap_size(heap) == 0;
}