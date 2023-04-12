#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

node_ptr_t create_node(int value) {
    node_ptr_t p = (node_ptr_t)malloc(sizeof(node_t));
    if (p == NULL) {
        perror("malloc() failed");
        exit(EXIT_FAILURE);
    }
    p->prev = p->next = NULL;
    p->value = value;

    return p;
}


// Create head node
void init(node_ptr_t *head) {
    *head = create_node(-1);
}


bool empty(const node_ptr_t head) {
    return head->next == NULL ? true : false;
}


// O(1)
void insert_to_head(node_ptr_t *head, int value) {
    node_ptr_t p = create_node(value);
    p->prev = (*head);
    p->next = (*head)->next;
    if ((*head)->next) {
        (*head)->next->prev = p;
    }
    (*head)->next = p;
}


node_ptr_t get_tail(const node_ptr_t head) {
    node_ptr_t p = head;
    while (p->next) {
        p = p->next;
    }

    return p;
}

/*
O(n)
Maintain a tail pointer for reduce to O(1)
*/
void insert_to_tail(node_ptr_t *head, int value) {
    node_ptr_t p = get_tail(*head);
    node_ptr_t q = create_node(value);
    q->prev = p;
    p->next = q;
}


// O(1)
int delete_first_node(node_ptr_t *head, int *value) {
    if (empty(*head)) {
        return FAILURE;
    }

    node_ptr_t p = (*head)->next;
    *value = p->value;
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);

    return SUCCESS;
}


/*
O(n)
Maintain a tail pointer for reduce to O(1)
*/
int delete_last_node(node_ptr_t *head, int *value) {
    if (empty(*head)) {
        return FAILURE;
    }

    node_ptr_t tail = get_tail(*head);
    tail->prev->next = tail->next;
    free(tail);

    return SUCCESS;
}


void destroy(node_ptr_t *head) {
    node_ptr_t p, q;
    for (p=(*head); p; p=q) {
        q = p->next;
        free(p);
    }
    (*head) = NULL;
}


void travel(const node_ptr_t head) {
    if (head) {
        for (node_ptr_t p=head->next; p; p=p->next) {
            printf("%d\t", p->value);
        }
        if (head->next) {
            printf("\n");
        }
    }
}
