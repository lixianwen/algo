#include <stdio.h>
#include <stdlib.h>
#include "sequence_queue.h"

void init(queue_ptr_t q, int size) {
    if (size < 1) {
        exit(EXIT_FAILURE);
    }

    q->size = size;
    q->head = q->tail = 0;
    q->array = (int *)malloc(sizeof(int) * size);
}


bool empty(const queue_ptr_t q) {
    return q->head == q->tail ? true : false;
}


bool full(const queue_ptr_t q) {
    return q->tail == q->size ? true : false;
}


// O(1)
bool enqueue(queue_ptr_t q, int value) {
    if (full(q)) {
        // queue is totally full
        if (q->head == 0) {
            return FAILURE;
        }

        // move the data to the head of queue
        for (int i=q->head; i<q->tail; i++) {
            q->array[i-q->head] = q->array[i];
        }

        q->tail -= q->head;
        q->head = 0; 
    }

    q->array[q->tail++] = value;

    return SUCCESS;
}


// O(1)
bool dequeue(queue_ptr_t q, int *value) {
    if (empty(q)) {
        return FAILURE;
    }

    *value = q->array[q->head++];

    return SUCCESS;
}


void clear(queue_ptr_t q) {
    q->head = q->tail = 0;
}


void destroy(queue_ptr_t q) {
    q->size = q->head = q->tail = 0;
    free(q->array);
    q->array = NULL;
}


void travel(const queue_ptr_t q) {
    for (int i=q->head; i<q->tail; i++) {
        printf("%d\t", q->array[i]);
    }
    if (!empty(q)) {
        printf("\n");
    }
}
