#include "tree.h"

void node_init(Node *node, void *value)
{
    node->value = value;
    node->parent = NULL;
    node->children = array_list_new();
}

Node *node_new(void *value)
{
    Node *node = malloc(sizeof(Node));
    node_init(node, value);
    return node;
}

void node_destroy(Node *node)
{
    for (size_t i = 0; i < node->children->size; i++)
    {
        Node *child = array_list_get(node->children, i);
        node_destroy(child);
    }

    array_list_destroy(node->children);
    free(node);
}

Node *node_append(Node *parent, void *value)
{
    Node *node = node_new(value);
    if (parent == NULL)
    {
        return node;
    }

    node->parent = parent;
    array_list_add(parent->children, node);
    return node;
}

size_t node_degree(Node *node)
{
    return array_list_len(node->children);
}
