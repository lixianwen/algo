#ifndef _HASHTABLE_H
#define _HASHTABLE_H

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
    struct node *next;
} node_t, *node_ptr_t;

/*
LinkedHashMap
*/
typedef struct {
    unsigned int count;
    node_ptr_t array[DEFAULT_INITIAL_CAPACITY];
} linked_hashmap, *linked_hashmap_ptr;

node_ptr_t create_node(int key, int value);
void init(linked_hashmap_ptr h);
void insert(linked_hashmap_ptr h, node_ptr_t n);
node_ptr_t search(const linked_hashmap_ptr h, int key);
void delete(linked_hashmap_ptr h, int key);
void travel(const linked_hashmap_ptr h);
void destroy(linked_hashmap_ptr h);

#endif