/*
Merge two ordered array a[p...q] and a[q+1...r] to array `a`

Time complexity: O(n) + O(n) -> O(2n) -> O(n)
Space complexity: O(n)
*/
void merge(int a[], int p, int q, int r) {
    int n = r - p + 1;
    int tmp[n];
    int i = p;
    int j = q + 1;
    int k = 0;

    while (i <= q && j<=r) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
        }
    }

    // 判断哪个子数组中有剩余数据
    int start = i, end = q;
    if (j <= r) {
        start = j;
        end = r;
    }

    // 将剩余数据拷贝到临时数组
    while (start <= end) {
        tmp[k++] = a[start++];
    }

    // 将合并后的有序数组 tmp 拷贝到 a
    for (int l=0; l<n; l++) {
        a[p+l] = tmp[l];
    }
}


/*
递推公式：merge_sort_recursion(p...r) = merge(merge_sort_recursion(p...q), merge_sort_recursion(q+1...r))
终止条件：p == r
*/
void merge_sort_recursion(int a[], int p, int r) {
    if (p == r) return;

    int q = (p + r) / 2;
    merge_sort_recursion(a, p, q);
    merge_sort_recursion(a, q+1, r);
    merge(a, p, q, r);
}


/*
Time complexity: T(n) = 2 * T(n/2) + n -> T(n) = O(nlogn)
Space complexity: O(n)
Stability: condition `a[i] <= a[j]` in function `merge` promise to be stable
*/
void merge_sort(int a[], int n) {
    merge_sort_recursion(a, 0, n-1);
}
