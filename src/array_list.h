#pragma once

#include <stdlib.h>
#include <stdbool.h>

struct ArrayList {
    void **data;
    size_t size;
    size_t capacity;
};
typedef struct ArrayList ArrayList;

// init, delete
ArrayList *array_list_new();
void array_list_destroy(ArrayList *list);


// methods
size_t array_list_len(ArrayList *list);
bool array_list_empty(ArrayList *list);

void array_list_add(ArrayList *list, void *value);
void* array_list_get(ArrayList *list, size_t index);
void array_list_set(ArrayList *list, size_t index, void *value);
void* array_list_remove(ArrayList *list, size_t index);
