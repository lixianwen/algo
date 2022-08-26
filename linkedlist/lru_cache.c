/*
This is the implemention of lru cache only using singly linkedlist.

维护一个时间有序的单链表，越靠近尾部的结点是越早之前的访问的
当有一个新的数据被访问时，我们从链表的头部开始顺序遍历链表
1. 如果被访问的数据在链表中存在，则从链表中把它删除然后插入到头部
2. 如果被访问的数据不在链表中：
 - 如果链表已满，删除最后一个结点并把被访问的数据插入到头部
 - 如果链表没满，直接插入到头部

 第一步总是要遍历链表，（缓存访问的）时间复杂度是 O(n)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 10

typedef struct _node {
    int key;
    int value;
    struct _node *next;
} Node, *NodePtr;

typedef struct {
    NodePtr head;
} LinkedList;

NodePtr createNode(int key, int value)
{
    NodePtr p = (NodePtr)malloc(sizeof(Node));
    if (p == NULL) {
        fprintf(stderr, "malloc failed at line %d\n", __LINE__ -2);
        exit(EXIT_FAILURE);
    }

    p->key = key;
    p->value = value;
    p->next = NULL;

    return p;
}

bool empty(const LinkedList *l)
{
    return l->head->next == NULL ? true : false;
}

/*
Search linear index for key in linkedlist, return -1 if key not in linkedlist.
O(n)
*/
int search(const LinkedList *l, int key)
{
    int linear_index = -1;
    int count = 1;
    for (NodePtr p=l->head->next; p; p=p->next) {
        if (p->key == key) {
            linear_index = count;
            break;
        } else {
            count++;
        }
    }

    return linear_index;
}

/*
Remove node in linkedlist match index and return its value.
O(n)
*/
void delete(LinkedList *l, int linear_index, int *value)
{
    if (!empty(l) && linear_index > 0) {
        NodePtr p = l->head;
        int count = 1;
        while (p && count < linear_index) {
            p = p->next;
            count++;
        }
        if (p && p->next) {
            NodePtr q = p->next;    // q is the node to be delete
            *value = q->value;
            p->next = q->next;
            free(q);
        }
    }
}

/*
Remove the *last* node in linkedlist.
O(n)
*/
void removeTail(LinkedList *l)
{
    if (!empty(l)) {
        NodePtr p = l->head;
        while (p->next->next) {
            p = p->next;
        }
        free(p->next);
        p->next = NULL;
    }
}

/*
Insert new node into linkedlist after head node
O(1)
*/
void insertHead(LinkedList *l, int key, int value)
{
    NodePtr p = createNode(key, value);
    p->next = l->head->next;
    l->head->next = p;
}

/* Dummy function for fetch key's value from storage like database. */
int fetchResult(int key)
{
    return 42;
}

/* Destroy the whole linkedlist */
void destroy(LinkedList *l)
{
    NodePtr p, q;
    for (p=l->head; p; p=q) {
        q = p->next;
        free(p);
    }
}

unsigned int length(const LinkedList *l)
{
    unsigned int len = 0;
    for (NodePtr p=l->head->next; p; p=p->next) {
        len++;
    }

    return len;
}

int lruCache(LinkedList *l, int key)
{
    int result;
    int linear_index = search(l, key);
    if (linear_index != -1) {     // key in linkedlist
        if (linear_index == 1) {  // key match the first node, so just get the value
            result = l->head->next->value;
        } else {
            delete(l, linear_index, &result);
            insertHead(l, key, result);
        }
    } else if (length(l) == MAXSIZE) {     // linkedlist is full
        removeTail(l);
        result = fetchResult(key);
        insertHead(l, key, result);
    } else {
        result = fetchResult(key);
        insertHead(l, key, result);
    }

    return result;
}

int main(void)
{
    LinkedList l, *p;
    p = &l;
    p->head = createNode(-1, -1);
    lruCache(p, 1);
    lruCache(p, 2);
    lruCache(p, 3);
    destroy(p);
    return 0;
}
