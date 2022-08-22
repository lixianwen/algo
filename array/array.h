#ifndef _ARRAY_H
#define _ARRAY_H

#include <stdbool.h>

typedef struct {
    int size;
    int used;   // 数组的长度（当前元素个数）
    int *arr;
} Array;

#define SUCCESS 0
#define FAILURE -1

int init(Array *l, int size);
void destroy(Array *l);
void clear(Array *l);
bool empty(const Array *l);
bool full(const Array *l);
int insert(Array *l, int pos, int value);
int delete(Array *l, int pos, int *value);
int get(const Array *l, int pos, int *value);
int search(const Array *l, int value);
int length(const Array *l);
void travel(const Array *l);

#endif