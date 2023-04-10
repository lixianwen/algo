#ifndef _SEQ_STACK_H
#define _SEQ_STACK_H

#include <stdbool.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct {
    int size;
    int count;
    int *array;
} stack_t, *stack_ptr_t;

void init(stack_ptr_t s, int size);
bool empty(const stack_ptr_t s);
bool full(const stack_ptr_t s);
int push(stack_ptr_t s, int value);
int pop(stack_ptr_t s, int *value);
void clear(stack_ptr_t s);
void destroy(stack_ptr_t s);
void travel(const stack_ptr_t s);

# endif