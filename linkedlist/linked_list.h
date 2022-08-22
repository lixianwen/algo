#ifndef _LinkedList_H
#define _LinkedList_H

#include <stdbool.h>

typedef struct _node {
    int value;
    struct _node *next;
} Node, *NodePtr;

typedef struct {
    NodePtr head;
    NodePtr tail;
} LinkedList;

#define SUCCESS 0
#define FAILURE -1

void init(LinkedList *l);
NodePtr createNode(int value);
void insertToHead(LinkedList *l, int value);
void insertToTail(LinkedList *l, int value);
int insert(LinkedList *l, int linear_index, int value, bool before);
int search(const LinkedList *l, int value);
int deleteHead(LinkedList *l, int *value);
int deleteTail(LinkedList *l, int *value);
int delete(LinkedList *l, int linear_index, int *value);
void clear(LinkedList *l);
void destroy(LinkedList *l);
bool empty(const LinkedList *l);
void travel(const LinkedList *l);
unsigned int length(const LinkedList *l);

#endif