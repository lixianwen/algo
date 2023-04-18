#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

void init(linked_hashmap_ptr h) {
    h->count = 0;

    // create sentinel
    for (int i=0; i<DEFAULT_INITIAL_CAPACITY; i++) {
        node_ptr_t p = (node_ptr_t)malloc(sizeof(node_t));
        p->next = NULL;
        h->array[i] = p;
    }
}


/*
Insertion time complexity: O(1)
*/
void insert(linked_hashmap_ptr h, node_ptr_t n) {
    double factor = (double)(h->count) / DEFAULT_INITIAL_CAPACITY;
    // reach threshold, increase its capacity
    if(factor > DEFAULT_LOAD_FACTOR) {
        free(n);
        return;
    }

    unsigned int index = hash(n->key);
    node_ptr_t head = h->array[index];
    n->next = head->next;
    head->next = n;
    h->count++;
}


node_ptr_t create_node(int key, int value) {
    node_ptr_t n = (node_ptr_t)malloc(sizeof(node_t));
    if (n == NULL) {
        fprintf(stderr, "malloc failed in file %s at line %d\n", __FILE__, __LINE__-2);
        exit(EXIT_FAILURE);
    }

    n->key = key;
    n->value = value;
    n->next = NULL;

    return n;
}


/*
Search time complexity: near O(1)
*/
node_ptr_t search(const linked_hashmap_ptr h, int key) {
    unsigned int index = hash(key);
    node_ptr_t n = h->array[index]->next;
    while (n) {
        if (n->key == key) {
            break;
        }
        n = n->next;
    }

    return n;
}


/*
Deletion time complexity: near O(1)
*/
void delete(linked_hashmap_ptr h, int key) {
    unsigned int index = hash(key);
    node_ptr_t p, n = h->array[index];
    while ((p=n->next)) {
        if (p->key == key) {
            n->next = p->next;
            free(p);
            h->count--;
            break;
        } else {
            n = p;
        }   
    }
}


void travel(const linked_hashmap_ptr h) {
    for (int i=0; i<DEFAULT_INITIAL_CAPACITY; i++) {
        for (node_ptr_t j=h->array[i]->next; j; j=j->next) {
            printf("%d\t", j->value);
        }
        printf("\n");
    }
}


void destroy(linked_hashmap_ptr h) {
    for (int i=0; i<DEFAULT_INITIAL_CAPACITY; i++) {
        node_ptr_t j, k;
        for (j=h->array[i]; j; j=k) {
            k = j->next;
            free(j);
        }
        h->array[i] = NULL;
    }
    h->count = 0;
}
