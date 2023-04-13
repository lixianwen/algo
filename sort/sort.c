#include <stdio.h>
#include <stdbool.h>

void swap(int *a, int *b) {
    *a = *a - *b;
    *b = *a + *b;
    *a = *b - *a;
}


/*
Time complexity: O(n^2)
Space complexity: O(1), aka sorted inplace
Stability: stable
*/
void bubble_sort(int a[], int n) {
    if (n < 2) return;

    for (int i=0; i<n; i++) {
        // 提前退出冒泡循环的标志位
        bool flag = false;
        for (int j=0; j<n-i-1; j++) {
            if (a[j] > a[j+1]) {  // compare
                // swap
                swap(&a[j], &a[j+1]);
                flag = true;
            }
        }
        if (!flag) break;  // 没有数据交换, 提前退出
    }
}
