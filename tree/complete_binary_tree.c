#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
如果结点 x 存储在数组下标为 i 的位置
结点 x 的左子树的下标为 2 * i
结点 x 的右子树的下标为 2 * i + 1
结点 x 的双亲结点的下标是 i/2
*/

void init(int cbt[], int n) {
    for (int i=0; i<n; i++) {
        cbt[i] = 0;  // zero indicate null
    }
}


/*
Store root node at index one.
If root node is null, the whole tree is empty.
*/
bool empty(const int cbt[]) {
    return cbt[1] == 0 ? true : false;
}


void create(int cbt[], int n) {
    int j;
    for (int i=1; i<n; i++) {
        scanf("%d", &j);
        // -1 as EOF
        if (j == -1) {
            break;
        } else if (i != 1 && j != 0 && cbt[i/2] == 0) {
            fprintf(stderr, "出现无双亲的非根结点, 编号: %d, 结点的值: %d\n", i, j);
            exit(EXIT_FAILURE);
        } else {
            cbt[i] = j;
        }
    }
}


int tree_height(const int cbt[], int n) {
    if (empty(cbt)) return -1;

    int i, j = 0;
    // find the last node
    for (i=n-1; i>0; i--) {
        if (cbt[i] != 0) {
            break;
        }
    }

    while (true) {
        if (i >= (1 << j) && i < (1 << (j+1))) {
            break;
        } else {
            j++;
        }
    }

    return j;
}
