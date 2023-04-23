/*
Construct binary tree with linked list.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node {
    char data;
    struct node *left_child;
    struct node *right_child;
} node_t, *node_ptr_t;

bool empty(const node_ptr_t t) {
    return t == NULL ? true : false;
}


node_ptr_t create_node(void) {
    node_ptr_t p = (node_ptr_t)malloc(sizeof(node_t));
    if (p == NULL) {
        fprintf(stderr, "Malloc failed");
        exit(EXIT_FAILURE);
    }

    p->left_child = p->right_child = NULL;

    return p;
}


/*
'#' indicate node x hasn't left child or right child

pre order insertion
*/
void construct(node_ptr_t *t) {
    char ch;
    scanf("%c", &ch);

    if (ch == '#') {
        *t = NULL;
    } else {
        *t = create_node();
        (*t)->data = ch;
        construct(&(*t)->left_child);
        construct(&(*t)->right_child);
    }
}


/*
post order deletion
*/
void destroy(node_ptr_t *t) {
    if (!empty(*t)) {
        destroy(&(*t)->left_child);
        destroy(&(*t)->right_child);

        free(*t);
        *t = NULL;
    }
}


/*
tree_height = max(height(left_child), height(right_child)) + 1
*/
int height(const node_ptr_t t) {
    if (empty(t)) return -1;

    int i, j;
    i = height(t->left_child);
    j = height(t->right_child);

    return i > j ? i + 1 : j + 1;
}


/*
A binary tree's maximum depth is the number of nodes along the longest path 
from the root node down to the farthest leaf node.
*/
int max_depth(const node_ptr_t t) {
    if (empty(t)) return 0;

    int i, j;
    i = max_depth(t->left_child);
    j = max_depth(t->right_child);

    return i > j ? i + 1 : j + 1;
}


/*
Time complexity: O(n)
*/
void pre_order_travel(const node_ptr_t t) {
    if (empty(t)) return;

    printf("%c\t", t->data);
    pre_order_travel(t->left_child);
    pre_order_travel(t->right_child);
}


/*
Time complexity: O(n)
*/
void in_order_travel(const node_ptr_t t) {
    if (empty(t)) return;

    in_order_travel(t->left_child);
    printf("%c\t", t->data);
    in_order_travel(t->right_child);
}


/*
Time complexity: O(n)
*/
void post_order_travel(const node_ptr_t t) {
    if (empty(t)) return;

    post_order_travel(t->left_child);
    post_order_travel(t->right_child);
    printf("%c\t", t->data);
}


int main(void) {
    node_ptr_t bt = NULL;
    construct(&bt);
    int h = height(bt);
    post_order_travel(bt);
    destroy(&bt);
    return 0;
}