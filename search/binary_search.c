/*
Time complexity: O(logn)
Space complexity: O(1)
*/
int simplest_binary_search(int a[], int n, int value) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if (a[mid] == value) {
            return mid;
        } else if (a[mid] < value) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}


/*
递推公式：bs(p...r) = bs(p...q-1) + bs(q+1...r)
终止条件：p > r

Time complexity: O(logn)
Space complexity: O(1)
*/
int internal_recursion_binary_search(int a[], int p, int r, int value) {
    if (p > r) return -1;

    int q = p + ((r - p) >> 1);
    if (a[q] == value) {
        return q;
    } else if (a[q] < value) {
        return internal_recursion_binary_search(a, q+1, r, value);
    } else {
        return internal_recursion_binary_search(a, p, q-1, value);
    }
}


int recursion_binary_search(int a[], int n, int value) {
    internal_recursion_binary_search(a, 0, n-1, value);
}


/*
Find the FIRST element equal to specific value in array `a`
*/
int bs1(int a[], int n, int value) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if (a[mid] < value) {
            low = mid + 1;
        } else if (a[mid] > value) {
            high = mid -1;
        } else {
            if (mid == 0 || a[mid-1] != value) {
                return mid;
            } else {
                high = mid -1;
            }
        }
    }

    return -1;
}


/*
Find the LAST element equal to specific value in array `a`
*/
int bs2(int a[], int n, int value) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if (a[mid] < value) {
            low = mid + 1;
        } else if (a[mid] > value) {
            high = mid - 1;
        } else {
            if (mid == n-1 || a[mid+1] != value) {
                return mid;
            } else {
                low = mid + 1;
            }
        }
    }

    return -1;
}


/*
Find the FIRST element `i` >= specific value in array `a`
*/
int bs3(int a[], int n, int value) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if (a[mid] >= value) {
            if (mid == 0 || a[mid-1] < value) {
                return mid;
            } else {
                high = mid - 1;
            }
        } else {
            low = mid + 1;
        }
    }

    return -1;
}


/*
Find the LAST element `i` <= specific value in array `a`
*/
int bs4(int a[], int n, int value) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if (a[mid] <= value) {
            if (mid == n-1 || a[mid+1] > value) {
                return mid;
            } else {
                low = mid + 1;
            }
        } else {
            high = mid - 1;
        }
    }

    return -1;
}
