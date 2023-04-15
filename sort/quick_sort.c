void swap(int *a, int *b) {
    if (a != b) {
        *a = *a - *b;
        *b = *a + *b;
        *a = *b - *a;
    }
}


/*
Select a pivot, partition array `a` and return the pivot

Time complexity: O(n)
Space complexity: O(1), aka sort inplace
Stability: unstable
*/
int partition(int a[], int p, int r) {
    int i = p, j = p;
    int q = a[r];
    while (j < r) {
        if (a[j] < q) {
            swap(&a[i++], &a[j++]);
        } else {
            j++;
        }
    }
    swap(&a[i], &a[j]);

    return i;
}


/*
递推公式：quick_sort(n) = quick_sort(p...q-1) + quick_sort(q+1...r)
终止条件：p >= r

Time complexity: When array `a` is in order, backward to O(n^2), otherwise O(nlogn)
Space complexity: O(1), aka sort inplace
Stability: unstable
*/
void quick_sort_recursion(int a[], int p, int r) {
    if (p >= r) return;

    int q = partition(a, p, r);
    quick_sort_recursion(a, p, q-1);
    quick_sort_recursion(a, q+1, r);
}


void quick_sort(int a[], int n) {
    quick_sort_recursion(a, 0, n-1);
}
