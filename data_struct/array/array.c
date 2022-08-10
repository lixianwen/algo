#include <stdio.h>
#include <stdlib.h>
#include "array.h"

int init(Array *l, int size)
{
    if (size < 1) {
        return FAILURE;
    }

    l->size = size;
    l->used = 0;
    int *p = (int *)malloc(sizeof(int) * size);
    if (p == NULL) {
        return FAILURE;
    }
    l->arr = p;

    return SUCCESS;
}

void destroy(Array *l)
{
    free(l->arr);
    l->size = 0;
    l->used = 0;
    l->arr = NULL;
}

void clear(Array *l)
{
    l->used = 0;
}

bool empty(const Array *l)
{
    return l->used == 0 ? true : false;
}

bool full(const Array *l)
{
    return l->used == l->size ? true : false;
}

/*
:param: pos start from one
O(n)
*/
int insert(Array *l, int pos, int value)
{
    if (full(l) || pos < 1 || pos > l->used + 1) {
        return FAILURE;
    }

    if (pos <= l->used) {
        for (int i=l->used; i>=pos; i--) {
            // *(l->arr+i) = *(l->arr+i-1);
            l->arr[i] = l->arr[i-1];
        }
    }

    // *(l->arr+pos-1) = value;
    l->arr[pos-1] = value;
    l->used++;

    return SUCCESS;
}

/*
:param: pos start from one
O(n)
*/
int delete(Array *l, int pos, int *value)
{
    if (empty(l) || pos < 1 || pos > l->used) {
        return FAILURE;
    }

    *value = l->arr[pos-1];
    for (int i=pos; i<l->used; i++) {
        l->arr[i-1] = l->arr[i];
    }
    l->used--;

    return SUCCESS;
}

/*
random access storage
O(1)
*/
int get(const Array *l, int pos, int *value)
{
    if (empty(l) || pos < 1 || pos > l->used) {
        return FAILURE;
    }

    *value = l->arr[pos-1];

    return SUCCESS;
}

/*
Assume this array is unordered.
Return -1 if `value` not in array, otherwise return its index equal to `value`
O(n) by brute force
*/
int search(const Array *l, int value)
{
    int index = -1;
    for (int i=0; i<l->used; i++) {
        if (l->arr[i] == value) {
            index = i;
            break;
        }
    }

    return index;
}

int length(const Array *l)
{
    return l->used;
}

void travel(const Array *l)
{
    for (int i=0; i<l->used; i++) {
        printf("%d ", l->arr[i]);
    }
    printf("\n");
}