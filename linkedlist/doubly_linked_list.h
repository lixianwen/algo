#ifndef _DOUBLY_LINKED_LIST_H
#define _DOUBLY_LINKED_LIST_H

#include <stdbool.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct _node {
    int value;
    struct _node *prev;
    struct _node *next;
} node_t, *node_ptr_t;

void init(node_ptr_t *head);
node_ptr_t create_node(int value);
bool empty(const node_ptr_t head);
void insert_to_head(node_ptr_t *head, int value);
void insert_to_tail(node_ptr_t *head, int value);
int delete_first_node(node_ptr_t *head, int *value);
int delete_last_node(node_ptr_t *head, int *value);
void destroy(node_ptr_t *head);
void travel(const node_ptr_t head);

#endif