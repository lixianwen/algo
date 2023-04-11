#ifndef _SEQ_QUEUE_H
#define _SEQ_QUEUE_H

#include <stdbool.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct {
    int size;
    int head;
    int tail;
    int *array;
} queue_t, *queue_ptr_t;

void init(queue_ptr_t q, int size);
bool empty(const queue_ptr_t q);
bool full(const queue_ptr_t q);
bool enqueue(queue_ptr_t q, int value);
bool dequeue(queue_ptr_t q, int *value);
void clear(queue_ptr_t q);
void destroy(queue_ptr_t q);
void travel(const queue_ptr_t q);

#endif