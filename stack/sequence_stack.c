#include <stdio.h>
#include <stdlib.h>
#include "sequence_stack.h"

void init(stack_ptr_t s, int size) {
    if (size < 1) {
        exit(EXIT_FAILURE);
    }
    s->size = size;
    s->count = 0;
    s->array = (int *)malloc(sizeof(int) * size);
}


bool empty(const stack_ptr_t s) {
    return s->count == 0 ? true : false;
}


bool full(const stack_ptr_t s) {
    return s->count == s->size ? true : false;
}


// O(1)
int push(stack_ptr_t s, int value) {
    if (full(s)) {
        return FAILURE;
    }

    s->array[s->count++] = value;

    return SUCCESS;
}


// O(1)
int pop(stack_ptr_t s, int *value) {
    if (empty(s)) {
        return FAILURE;
    }

    *value = s->array[--s->count];
    return SUCCESS;
}


void clear(stack_ptr_t s) {
    s->count = 0;
}


void destroy(stack_ptr_t s) {
    free(s->array);
    s->size = 0;
    s->count = 0;
    s->array = NULL;
}


void travel(const stack_ptr_t s) {
    for (int i=s->count; i>0; i--) {
        printf("%d\t", s->array[i-1]);
    }
    if (s->count) {
        printf("\n");
    }
}
