#include <stdio.h>
#include <stdlib.h>


void swap(int *a, int *b) {
    *a = *a - *b;
    *b = *a + *b;
    *a = *b - *a;
}


void bottom_to_top_heapify(int a[], int tail) {
    while (tail > 1) {
        int parent_index = tail / 2;
        if (parent_index > 0 && a[parent_index] > a[tail]) {
            swap(&a[parent_index], &a[tail]);
        } else {
            break;
        }
        tail = parent_index;
    }
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int * top_k(int *nums, int n, int k){
    if (n < 1 || k < 1) return NULL;

    int *array = (int *)malloc(sizeof(int) * k);
    int count = 0;

    for (int i=0; i<n; i++) {
        if (count < k) {
            array[++count] = nums[i];
            bottom_to_top_heapify(array, count);
        } else {
            if (nums[i] > array[1]) {
                swap(&array[1], &array[count]);
                array[count] = nums[i];
                bottom_to_top_heapify(array, count);
            }
        }
    }

    return array;
}


int main(void) {
    int nums[] = {1};
    int k = 1;
    int *p = top_k(nums, sizeof(nums)/sizeof(int), k);
    for (int i=1; i<=k; i++) {
        printf("array[%d] = %d\n", i, p[i]);
    }
    free(p);
    return 0;
}
