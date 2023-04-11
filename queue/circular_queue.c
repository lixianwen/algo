#include <stdio.h>
#include "sequence_queue.h"

bool circular_full(const queue_ptr_t q) {
    return (q->tail + 1) % q->size == q->head ? true : false;
}

// O(1)
bool circular_enqueue(queue_ptr_t q, int value) {
    if (circular_full(q)) {
        return FAILURE;
    }

    q->array[q->tail] = value;
    q->tail = (q->tail + 1) % q->size;

    return SUCCESS;
}


// O(1)
bool circular_dequeue(queue_ptr_t q, int *value) {
    if (empty(q)) {
        return FAILURE;
    }

    *value = q->array[q->head];
    q->head = (q->head + 1) % q->size;

    return SUCCESS;
}


void circular_travel(const queue_ptr_t q) {
    int head = q->head;
    int tail = q->tail;
    int size = q->size;
    for (int i=head; i!=tail; i=(i+1)%size) {
        printf("%d\t", q->array[i]);
    }
    if (head != tail) {
        printf("\n");
    }
}
