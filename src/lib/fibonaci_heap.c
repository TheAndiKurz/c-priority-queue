#include "fibonaci_heap.h"

void fibonaci_heap_init(FibonaciHeap *heap, int (*compare)(void *, void *))
{
    heap->size = 0;
    heap->min = NULL;
    heap->roots = array_list_new();
    heap->compare = compare;
}

FibonaciHeap *fibonaci_heap_new(int (*compare)(void *, void *))
{
    FibonaciHeap *heap = malloc(sizeof(FibonaciHeap));
    fibonaci_heap_init(heap, compare);
    return heap;
}

void fibonaci_heap_destroy(FibonaciHeap *heap)
{
    for (size_t i = 0; i < heap->roots->size; i++)
    {
        Node *node = array_list_get(heap->roots, i);
        node_destroy(node);
    }

    array_list_destroy(heap->roots);
    free(heap);
}

// heap operations
size_t fibonaci_heap_size(FibonaciHeap *heap)
{
    return heap->size;
}

bool fibonaci_heap_is_empty(FibonaciHeap *heap)
{
    return heap->size == 0;
}

void fibonaci_heap_push(FibonaciHeap *heap, void *value)
{
    Node *node = node_new(value);
    array_list_add(heap->roots, node);
    heap->size++;

    if (heap->min == NULL || heap->compare(heap->min->value, node->value) > 0)
    {
        heap->min = node;
    }
}

void *fibonaci_heap_peek(FibonaciHeap *heap)
{
    return heap->min->value;
}

/**
 * @brief a function to cut out a node and put it into the root of the heap
 *
 * @param heap
 * @param node
 */
void cut_out(FibonaciHeap *heap, Node *node)
{
    Node *parent = node->parent;
    if (parent == NULL)
    {
        return;
    }

    array_list_remove_item(parent->children, node);
    node->parent = NULL;

    array_list_add(heap->roots, node);
    return node;
}

void merge_nodes(FibonaciHeap *heap, Node *node1, Node *node2)
{
    if (heap->compare(node1->value, node2->value) > 0)
    {
        Node *tmp = node1;
        node1 = node2;
        node2 = tmp;
    }

    array_list_add(node1->children, node2);
    node2->parent = node1;
}

void fibonaci_heap_clean_up(FibonaciHeap *heap)
{
    // merge roots
    ArrayList *degree_roots = array_list_new();

    for (size_t i = 0; i < array_list_len(heap->roots); i++)
    {
        Node *root = array_list_get(heap->roots, i);
        size_t degree = node_degree(root);

        while ((Node *other = array_list_get(degree_roots, degree)) != NULL)
        {
            merge_nodes(root, other);
            degree = node_degree(root);
        }
        array_list_set(degree_roots, degree, root);
    }

    // get new roots
    ArrayList *new_roots = array_list_new();
    for (size_t i = 0; i < array_list_len(degree_roots); i++)
    {
        Node *root = array_list_get(degree_roots, i);
        if (root != NULL)
        {
            array_list_add(new_roots, root);
        }
    }

    array_list_destroy(degree_roots);
    array_list_destroy(heap->roots);
    heap->roots = new_roots;

    // get new min
    heap->min = NULL;
    for (size_t i = 0; i < array_list_len(heap->roots); i++)
    {
        Node *root = array_list_get(heap->roots, i);
        if (heap->min == NULL || heap->compare(heap->min->value, root->value) > 0)
        {
            heap->min = root;
        }
    }
}

void *fibonaci_heap_pop(FibonaciHeap *heap)
{
    // extract min
    Node *min = array_list_remove_item(heap->roots, heap->min);
    void *value = min->value;

    // cut out min children
    for (size_t i = array_list_len(min->children) - 1; i >= 0; i--)
    {
        Node *child = array_list_get(min->children, i);
        cut_out(heap, child);
    }

    fibonaci_heap_clean_up(heap);

    return value;
}