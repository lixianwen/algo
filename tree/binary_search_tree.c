/*
二叉搜索树的查找、插入和删除操作的时间复杂度：
    最坏时间复杂度：左斜树和右斜树，即退化成链表，时间复杂度为 O(n)
    最好情况复杂度：完全二叉树（满二叉树是完全二叉树的一种特殊情况），时间复杂度为 O(logn)
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left_child;
    struct node *right_child;
} node_t, *node_ptr_t;


bool empty(const node_ptr_t t) {
    return t == NULL ? true : false;
}


node_ptr_t create_node(void) {
    node_ptr_t p = (node_ptr_t)malloc(sizeof(node_t));
    if (p == NULL) {
        fprintf(stderr, "Malloc failed");
        exit(EXIT_FAILURE);
    }

    p->left_child = p->right_child = NULL;

    return p;
}


node_ptr_t search(const node_ptr_t t, int key) {
    if (empty(t)) return NULL;

    if (t->data == key) {
        return t;
    } else if (t->data > key) {
        return search(t->left_child, key);
    } else {
        return search(t->right_child, key);
    }
}


void insert(node_ptr_t *t, int data) {
    if (empty(*t)) {
        (*t) = create_node();
        (*t)->data = data;
        return;
    }

    if ((*t)->data > data) {
        insert(&(*t)->left_child, data);
    } else {
        insert(&(*t)->right_child, data);
    }
}


void delete(node_ptr_t *t, int key) {
    node_ptr_t n = *t;
    node_ptr_t pn = NULL;
    while (n && n->data != key) {
        pn = n;
        if (n->data > key) {
            n = n->left_child;
        } else {
            n = n->right_child;
        }
    }

    if (n == NULL) return;  // not found

    // 要删除的结点有左子树和右子树
    if (n->left_child && n->right_child) {
        // 查找 n 的右子树的最小结点
        node_ptr_t min_n = n->right_child;
        node_ptr_t min_pn = n;
        while (min_n->left_child) {
            min_pn = min_n;
            min_n = min_n->left_child;
        }

        n->data = min_n->data;  // 把 min_n 的数据复制到 n，即 n 原来的数据已经被覆盖，相当于删除了 n 结点
        n = min_n;  // 下面就变成删除 min_n，即 n 的右子树的最小结点
        pn = min_pn;
    }

    // 要删除的结点是叶子节点或者只有一个孩子结点
    node_ptr_t child;
    if (n->left_child) {
        child = n->left_child;
    } else if (n->right_child) {
        child = n->right_child;
    } else {
        child = NULL;
    }

    if (pn == NULL) {  // 删除的是根结点且根结点只有左子树或右子树
        (*t) = child;
    } else if (pn->left_child == n) {
        pn->left_child = child;
    } else {
        pn->right_child = child;
    }
    free(n);
}


/*
支持插入重复数据
*/
void insert_v2(node_ptr_t *t, int data) {
    if (empty(*t)) {
        (*t) = create_node();
        (*t)->data = data;
        return;
    }

    if ((*t)->data > data) {
        insert_v2(&(*t)->left_child, data);
    } else if ((*t)->data < data) {
        insert_v2(&(*t)->right_child, data);
    } else {
        /*
        要插入的结点的值与当前结点的值相同
        把这个新插入的结点当作大于当前结点来处理
        */
       insert_v2(&(*t)->right_child, data);
    }
}


/*
支持查找重复数据
*/
void search_v2(const node_ptr_t t, node_ptr_t *result, int key) {
    if (empty(t)) return;

    if (t->data == key) {
        node_ptr_t p = create_node();
        p->data = t->data;
        (*result) = p;
        // 遇到值相同的结点，继续在该结点的右子树中查找，直到遇到叶子结点才停止
        search_v2(t->right_child, &(*result)->left_child, key);
    } else if (t->data > key) {
        search_v2(t->left_child, result, key);
    } else {
        search_v2(t->right_child, result, key);
    }
}


/*
支持删除重复数据
*/
void delete_v2(node_ptr_t *t, node_ptr_t *result) {
    while (*result) {
        delete(t, (*result)->data);
        node_ptr_t p = *result;
        *result = (*result)->left_child;
        free(p);
    }
}


node_ptr_t find_max_node(const node_ptr_t t) {
    if (empty(t) || empty(t->right_child)) return t;

    return find_max_node(t->right_child);
}


node_ptr_t find_min_node(const node_ptr_t t) {
    if (empty(t) || empty(t->left_child)) return t;

    return find_min_node(t->left_child);
}


node_ptr_t find_prev_node(const node_ptr_t t, node_ptr_t p) {
    if (p == NULL) return p;

    node_ptr_t n = t;
    node_ptr_t pn = NULL;
    while (n && n != p) {
        pn = n;
        if (n->data > p->data) {
            n = n->left_child;
        } else {
            n = n->right_child;
        }
    }

    return n == NULL ? n : pn;
}


void in_order_travel(const node_ptr_t t) {
    if (empty(t)) return;

    in_order_travel(t->left_child);
    printf("%d\t", t->data);
    in_order_travel(t->right_child);
}
