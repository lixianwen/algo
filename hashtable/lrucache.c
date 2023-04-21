#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
The default initial capacity - MUST be a power of two.
*/
#define DEFAULT_INITIAL_CAPACITY (1 << 4)

/*
The maximum capacity - MUST be a power of two.
*/
#define MAXIMUM_CAPACITY (1 << 7)

/*
The load factor is a measure of how full the hash table is allowed to get 
before its capacity is automatically increased.

load factor = number_of_elements / capacity
*/
#define DEFAULT_LOAD_FACTOR 0.75

#define MASK (DEFAULT_INITIAL_CAPACITY - 1)

/*
The hash function.
*/
#define hash(key) ((key) & MASK)

typedef struct node {
    int key;
    int value;
    struct node *prev;
    struct node *next;
    struct node *hprev;
    struct node *hnext;
} node_t, *node_ptr_t;


// LinkedHashMap
typedef struct {
    unsigned int count;
    node_ptr_t array[DEFAULT_INITIAL_CAPACITY];
} hashmap, *hashmap_ptr;

/*
Doubly linked list

越是最近访问的结点越靠近链表头部
*/
typedef struct {
    node_ptr_t head;
    node_ptr_t tail;
} dlist_t, *dlist_ptr_t;

node_ptr_t create_node(void) {
    node_ptr_t p = (node_ptr_t)malloc(sizeof(node_t));
    if (p == NULL) exit(EXIT_FAILURE);
    p->prev = p->next = p->hprev = p->hnext = NULL;

    return p;
}


void l_init(dlist_ptr_t l) {
    l->head = l->tail = create_node();
}


void l_attach(dlist_ptr_t l, node_ptr_t n) {
    if (l && n) {
        n->next = l->head->next;
        n->prev = l->head;
        if (l->head->next) {
            l->head->next->prev = n;
        } else {
            l->tail = n;
        }
        l->head->next = n;
    }
}


void l_separate(dlist_ptr_t l, node_ptr_t n) {
    if (l && n) {
        n->prev->next = n->next;
        if (n->next) {
            n->next->prev = n->prev;
        } else {
            l->tail = n->prev;
        }
    }
}


void h_init(hashmap_ptr h) {
    h->count = 0;

    // create sentinel
    for (int i=0; i<DEFAULT_INITIAL_CAPACITY; i++) {
        h->array[i] = create_node();
    }
}


void h_attach(node_ptr_t head, node_ptr_t n) {
    while (head && head->hnext) {
        head = head->hnext;
    }

    if (head && n) {
        n->hnext = head->hnext;
        n->hprev = head;
        head->hnext = n;
    }
}


void h_separate(node_ptr_t n) {
    if (n) {
        n->hprev->hnext = n->hnext;
        if (n->hnext) {
            n->hnext->hprev = n->hprev;
        }
    }
}


/*
Search time complexity: near O(1)
*/
node_ptr_t search(const hashmap_ptr h, int key) {
    unsigned int index = hash(key);
    node_ptr_t n = h->array[index]->hnext;
    while (n) {
        if (n->key == key) {
            break;
        } else {
            n = n->hnext;
        }
    }

    return n;
}


node_ptr_t find(const hashmap_ptr h, dlist_ptr_t l, int key) {
    node_ptr_t n = search(h, key);
    if (n) {
        l_separate(l, n);
        l_attach(l, n);
    }

    return n;
}


/*
Deletion time complexity: near O(1)
*/
void delete(hashmap_ptr h, dlist_ptr_t l, int key) {
    node_ptr_t n = search(h, key);
    if (n) {
        h_separate(n);
        l_separate(l, n);
        free(n);
        h->count--;
    }
}


/*
Insertion time complexity: near O(1)
*/
void insert(hashmap_ptr h, dlist_ptr_t l, int key, int value) {
    node_ptr_t n = find(h, l, key);
    if (n) return;

    n = create_node();
    n->key = key;
    n->value = value;

    unsigned int index = hash(key);
    node_ptr_t p = h->array[index];

    double factor = (double)(h->count) / DEFAULT_INITIAL_CAPACITY;
    if (factor >= DEFAULT_LOAD_FACTOR) {
        delete(h, l, l->tail->key);
    }
    h_attach(p, n);
    l_attach(l, n);

    h->count++;
}


void travel(const dlist_ptr_t l) {
    node_ptr_t n = l->head->next;
    for (; n; n=n->next) {
        printf("%d: %d\n", n->key, n->value);
    }
}


void destroy(hashmap_ptr h) {
    for (int i=0; i<DEFAULT_INITIAL_CAPACITY; i++) {
        node_ptr_t p, q;
        for (p=h->array[i]; p; p=q) {
            q = p->hnext;
            free(p);
        }
    }
}


int main(void) {
    srand(time(NULL));

    hashmap my_h;
    dlist_t my_l;
    hashmap_ptr my_h_ptr = &my_h;
    dlist_ptr_t my_l_prt = &my_l;
    h_init(my_h_ptr);
    l_init(my_l_prt);

    search(my_h_ptr, 42);
    int key = rand();
    insert(my_h_ptr, my_l_prt, key, 0);
    find(my_h_ptr, my_l_prt, key);
    delete(my_h_ptr, my_l_prt, key);

    for (int i=0; i<DEFAULT_INITIAL_CAPACITY; i++) {
        insert(my_h_ptr, my_l_prt, rand(), i);
    }
    find(my_h_ptr, my_l_prt, my_h_ptr->array[10]->hnext->key);

    travel(my_l_prt);
    destroy(my_h_ptr);
    free(my_l.head);

    return 0;
}