#include "array_list.h"

// init, delete
void array_list_init(ArrayList *list)
{
    list->size = 0;
    list->capacity = 8;
    list->data = malloc(sizeof(void *) * list->capacity);
}

ArrayList *array_list_new()
{
    ArrayList *list = malloc(sizeof(ArrayList));
    array_list_init(list);
    return list;
}

void array_list_destroy(ArrayList *list)
{
    free(list->data);
    free(list);
}

// methods
size_t array_list_len(ArrayList *list)
{
    return list->size;
}

bool array_list_empty(ArrayList *list)
{
    return list->size == 0;
}

void array_list_add(ArrayList *list, void *value)
{
    if (list->size == list->capacity)
    {
        list->capacity *= 2;
        list->data = realloc(list->data, sizeof(void *) * list->capacity);
    }
    list->data[list->size++] = value;
}

void *array_list_get(ArrayList *list, size_t index)
{
    if (index >= list->size)
    {
        return NULL;
    }
    return list->data[index];
}

void array_list_set(ArrayList *list, size_t index, void *value)
{
    if (index >= list->size)
    {
        return array_list_insert(list, index, value);
    }
    list->data[index] = value;
}

void *array_list_remove(ArrayList *list, size_t index)
{
    void *value = list->data[index];

    for (size_t i = index; i < list->size - 1; i++)
    {
        list->data[i] = list->data[i + 1];
    }
    list->size--;

    if (list->size == list->capacity / 4)
    {
        list->capacity /= 2;
        list->data = realloc(list->data, sizeof(void *) * list->capacity);
    }

    return value;
}

void *array_list_remove_item(ArrayList *list, void *item)
{
    for (size_t i = 0; i < list->size; i++)
    {
        if (list->data[i] == item)
        {
            return array_list_remove(list, i);
        }
    }
    return NULL;
}

void array_list_insert(ArrayList *list, size_t index, void *item)
{
    // make the list big enough to insert into this location
    if (index >= list->size)
    {
        while (list->size <= index)
        {
            array_list_add(list, NULL);
        }

        array_list_set(list, index, item);
        return;
    }

    array_list_add(list, array_list_get(list, list->size - 1));
    for (size_t i = list->size - 1; i > index; i--)
    {
        array_list_set(list, i, array_list_get(list, i - 1));
    }
    array_list_set(list, index, item);
}
