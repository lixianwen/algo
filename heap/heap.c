/*
一个包含 n 个结点的完全二叉树的树高不超过 logn
堆化的过程是顺着结点所在的路径比较交换的，所以堆化的时间复杂度和树高成正比，即 O(logn)
插入数据和删除堆顶元素的主要逻辑就是堆化，所以插入数据和删除堆顶元素的时间复杂度是 O(logn)
*/

#include <stdio.h>
#include <stdlib.h>

/*
The default initial capacity - MUST be a power of two.
*/
#define DEFAULT_INITIAL_CAPACITY (1 << 4)

typedef struct {
    unsigned int count;
    int array[DEFAULT_INITIAL_CAPACITY];
} heap_t, *heap_ptr_t;


void create(heap_ptr_t h, unsigned int n) {
    for (unsigned int i=1; i<n; i++) {
        int j;
        scanf("%d", &j);

        if (j == -1) {
            break;
        } else if (i != 1 && h->array[i/2] == 0 && j != 0) {
            fprintf(stderr, "出现无双亲的非根结点, 编号: %d, 结点的值: %d\n", i, j);
            exit(EXIT_FAILURE);
        } else {
            h->array[i] = j;
            h->count++;
        }
    }
}


void swap(int *a, int *b) {
    if (a != b) {
        *a = *a - *b;
        *b = *a + *b;
        *a = *b - *a;
    }
}


void insert(heap_ptr_t h, unsigned int n, int key) {
    if (h->count == n - 1) return;

    h->array[++(h->count)] = key;

    // heapify from bottom to top
    unsigned int index = h->count;
    while (index > 1) {
        unsigned int parent_index = index / 2;
        if (h->array[parent_index] < h->array[index]) {
            swap(&h->array[parent_index], &h->array[index]);
        } else {
            break;
        }
        index = parent_index;
    }
}


void delete_top_node(heap_ptr_t h, unsigned int n) {
    if (h->count == 0) return;

    h->array[1] = h->array[h->count--];  // deleted

    // heapify from top to bottom
    for (unsigned int i=1; i<n;) {
        unsigned int left = i * 2;
        unsigned int right = i * 2 + 1;
        if (h->array[i] < h->array[left]) {
            swap(&h->array[i], &h->array[left]);
            i = left;
        } else if (h->array[i] < h->array[right]) {
            swap(&h->array[i], &h->array[right]);
            i = right;
        } else {
            break;
        }
    }
}


int main(void) {
    // 一个大顶堆：33 27 21 16 13 15 19 5 6 7 8 1 2 -1
    heap_t h = {.count=0, .array={0}};
    create(&h, DEFAULT_INITIAL_CAPACITY);
    insert(&h, DEFAULT_INITIAL_CAPACITY, 12);
    delete_top_node(&h, DEFAULT_INITIAL_CAPACITY);
    return 0;
}
