/*
This is the implement of singly linked list with head node
*/

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void init(LinkedList *l)
{

    l->head = l->tail = createNode(-1);
}

NodePtr createNode(int value)
{
    NodePtr p = (NodePtr)malloc(sizeof(Node));
    if (p == NULL) {
        exit(EXIT_FAILURE);
    }
    p->value = value;
    p->next = NULL;

    return p;
}

/*
Insert new node as the first node after head node.
O(1)
*/
void insertToHead(LinkedList *l, int value)
{
    NodePtr p = createNode(value);
    p->next = l->head->next;
    l->head->next = p;
    if (p->next == NULL) {
        l->tail = p;
    }
}

/*
Insert new node as tail node.
O(1)
*/
void insertToTail(LinkedList *l, int value)
{
    NodePtr p = createNode(value);
    l->tail->next = p;
    l->tail = p;
}

/*
Insert node before or after linear index element.
Linear table index start from *ONE*, stand for each element.
O(n)
*/
int insert(LinkedList *l, int linear_index, int value, bool before)
{
    if (linear_index < 1) {
        return FAILURE;
    }

    NodePtr p = l->head;      // p point to head node 
    if (before) {
        for (int count=1; p && count<linear_index; count++) {
            p = p->next;
        }
    } else {
        for (int count=1; p && count<=linear_index; count++) {
            p = p->next;
        }
    }
    if (p == NULL) {     // The index - 1 or index element doesn't exist
        return FAILURE;
    }

    NodePtr q = createNode(value);
    q->next = p->next;
    p->next = q;
    if (q->next == NULL) {  // linked list is empty, before = true, linear_index = 1
        l->tail = q;
    }

    return SUCCESS;
}

bool empty(const LinkedList *l)
{
    return l->head == l->tail && l->head->next == NULL ? true : false;
}

/*
Free all nodes except head node.
*/
void clear(LinkedList *l)
{
    NodePtr p = l->head, q;
    for (p=p->next; p; p=q) {
        q = p->next;
        free(p);
    }
}

/*
Free all nodes include head node.
*/
void destroy(LinkedList *l)
{
    NodePtr p, q;
    for (p=l->head; p; p=q) {
        q = p->next;
        free(p);
    }
}

void travel(const LinkedList *l)
{
    NodePtr p = l->head;
    for (p=p->next; p; p=p->next) {
        printf("%d ", p->value);
    }
    printf("\n");
}

/*
Search for if `value` equal to `node->value`.
Return linear table index if match else -1.
// O(n)
*/
int search(const LinkedList *l, int value)
{
    int result = -1;
    int count = 1;
    NodePtr p = l->head->next;    // point to first node
    while (p) {
        if (p->value == value) {
            result = count;
            break;
        } else {
            p = p->next;
            count++;
        }
    }

    return result;
}

/*
Delete first node after head node.
O(1)
*/
int deleteHead(LinkedList *l, int *value)
{
    if (empty(l)) {
        return FAILURE;
    }

    NodePtr p = l->head->next;
    *value = p->value;
    l->head->next = p->next;
    if (p->next == NULL) {
        l->tail = l->head;
    }
    free(p);

    return SUCCESS;
}

/*
Delete tail node.
O(n)
*/
int deleteTail(LinkedList *l, int *value)
{
    if (empty(l)) {
        return FAILURE;
    }

    NodePtr p = l->head->next;       // point to first node
    NodePtr q = NULL;                // node before tail node
    while (p->next) {
        q = p;
        p = p->next;
    }
    *value = p->value;
    if (q) {
        q->next = NULL;
        l->tail = q;
        free(p);
    } else {       // only has one node
        free(p);
        l->head->next = NULL;
        l->tail = l->head;
    }

    return SUCCESS;
}

/*
Delete linear index node
O(1)
*/
int delete(LinkedList *l, int linear_index, int *value)
{
    if (empty(l) || linear_index < 1) {
        return FAILURE;
    }

    int count = 1;
    NodePtr p = l->head;        // point to head node
    while (p && count<linear_index) {
        p = p->next;
        count++;
    }
    if (p == NULL || p->next == NULL) {     // Linear index node doesn't exists or p is tail node
        return FAILURE;
    }

    NodePtr q = p->next;     // q is the node to be deleted
    *value = q->value;
    p->next = q->next;
    if (q->next == NULL) {  // q is the tail node
        l->tail = p;
    }
    free(q);

    return SUCCESS;
}

unsigned int length(const LinkedList *l)
{
    unsigned int len = 0;
    for (NodePtr p=l->head->next; p; p=p->next) {
        len++;
    }
    return len;
}