#pragma once

#include "array_list.h"

struct Node
{
    void *value;
    Node *parent;
    ArrayList children; // arraylist of Nodes
};
typedef struct Node Node;

Node *node_new(void *value);
void node_destroy(Node *node);

// node operations
Node *node_append(Node *parent, void *value);
size_t node_degree(Node *node);
