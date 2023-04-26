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


/*
heapify from top to bottom

n = h->count
*/
void top_to_bottom_heapify(int a[], unsigned int n, unsigned int i) {
    while (1) {
        unsigned int left = i * 2;
        unsigned int right = i * 2 + 1;
        unsigned int max_pos = i;
        if (left <=n && a[max_pos] < a[left]) max_pos = left;
        if (right <=n && a[max_pos] < a[right]) max_pos = right;
        if (max_pos == i) break;
        swap(&a[max_pos], &a[i]);
        i = max_pos;
    }
}

void delete_top_node(heap_ptr_t h) {
    if (h->count == 0) return;

    h->array[1] = h->array[h->count--];  // deleted
    top_to_bottom_heapify(h->array, h->count, 1);
}


/*
Build heap inplace.

Index between count/2 + 1 to count are leaf node.
Handle non leaf node between count/2 to 1

Time complexity: O(n)
*/
void build_heap(heap_ptr_t h) {
    for (unsigned int i=h->count/2; i>0; i--) {
        top_to_bottom_heapify(h->array, h->count, i);
    }
}


/*
Build heap first, then swap head and count.
Build heap again for head to count-1, then swap head and count-1.
Repeat it until count == 1

Time complexity: O(nlogn)
*/
void heap_sort(heap_ptr_t h) {
    build_heap(h);
    unsigned int i = h->count;
    while (i > 1) {
        swap(&h->array[i], &h->array[1]);
        top_to_bottom_heapify(h->array, --i, 1);
    }
}


int main(void) {
    // 一个大顶堆：33 27 21 16 13 15 19 5 6 7 8 1 2 -1
    heap_t h = {.count=0, .array={0}};
    create(&h, DEFAULT_INITIAL_CAPACITY);
    insert(&h, DEFAULT_INITIAL_CAPACITY, 12);
    delete_top_node(&h);
    heap_sort(&h);
    return 0;
}
