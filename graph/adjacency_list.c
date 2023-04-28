#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* The default initial capacity - MUST be a power of two. */
#define DEFAULT_INITIAL_CAPACITY (1 << 3)

#define SUCCESS 0
#define FAILURE -1

/* adjacent */
typedef struct adj {
    unsigned int index;
    struct adj *next;
} adjacent_t, *adjacent_ptr_t;

/* vertex */
typedef struct {
    char data;
    adjacent_ptr_t first_adjacent;
} vertex_t, *vertex_ptr_t;

typedef struct {
    /* adjacency list */
    vertex_ptr_t vexs[DEFAULT_INITIAL_CAPACITY];
    /* number of vertex */
    unsigned int vertexs;
    /* number of edge */
    unsigned int edges;
} graph_t, *graph_ptr_t;


void init(graph_ptr_t g, unsigned int n) {
    for (unsigned int i=0; i<n; i++) {
        g->vexs[i] = NULL;
    }
}


int construct(graph_ptr_t g, unsigned int n) {
    printf("Please input number of vertex & edge: \n");
    scanf("%d %d", &g->vertexs, &g->edges);
    if (g->vertexs < 1 || g->vertexs > n) return FAILURE;

    unsigned int type;
    printf("Please input graph type, 0 - undirected graphs, 1 - directed graphs\n");
    scanf("%d", &type);
    if (type == 0 && g->edges > (g->vertexs * (g->vertexs - 1)) / 2) return FAILURE;
    if (type == 1 && g->edges > g->vertexs * (g->vertexs - 1)) return FAILURE;

    for (unsigned int i=0; i<g->vertexs; i++) {
        char ch;
        scanf("\n%c", &ch);
        getchar();

        vertex_ptr_t p = (vertex_ptr_t)malloc(sizeof(vertex_t));
        if (p == NULL) exit(EXIT_FAILURE);
        p->data = ch;
        p->first_adjacent = NULL;
        g->vexs[i] = p;
    }

    /*
    construct edge table
    directed graphs for example
    */
    for (unsigned int k=0; k<g->edges; k++) {
        unsigned int i, j;
        printf("Please input edge (i, j)\n");
        scanf("%d %d", &i, &j);
        if (i > g->vertexs - 1) return FAILURE;
        if (j > g->vertexs - 1) return FAILURE;

        adjacent_ptr_t q = (adjacent_ptr_t)malloc(sizeof(adjacent_t));
        if (q == NULL) exit(EXIT_FAILURE);
        q->index = j;
        q->next = g->vexs[i]->first_adjacent;
        g->vexs[i]->first_adjacent = q;
    }

    return SUCCESS;
}


/*
:param vertex: element of g->vexs

:return: index of vertex in g->vexs
*/
int get_index(const graph_ptr_t g, char vertex) {
    int index = -1;

    for (unsigned int i=0; i<g->vertexs; i++) {
        if (g->vexs[i]->data == vertex) {
            index = i;
            break;
        }
    }

    return index;
}


/*
:param v1: element of g->vexs
:param v2: element of g->vexs

:return: true if vertex v1 & v2 has arc
*/
bool has_arc(const graph_ptr_t g, char v1, char v2) {
    bool result = false;
    int i = get_index(g, v1);
    int j = get_index(g, v2);
    if (i == -1 || j == -1) return result;

    adjacent_ptr_t p = g->vexs[i]->first_adjacent;
    for (; p; p=p->next) {
        if (p->index == (unsigned int)j) {
            result = true;
            break;
        }
    }

    return result;
}


/*
:param vertex: element of g->vexs

:return:
    vertex's outdegree if g->vexs is adjacency list
    vertex's indegree if g->vexs is reversed adjacency list
*/
unsigned int get_degree(const graph_ptr_t g, char vertex) {
    unsigned int degree = 0;
    int i = get_index(g, vertex);
    if (i == -1) return degree;

    adjacent_ptr_t p = g->vexs[i]->first_adjacent;
    while (p) {
        degree++;
        p = p->next;
    }

    return degree;
}


/*
:param vertex: element of g->vexs

:return: vertex's adjacents

Note: The returned array must be malloced, assume caller calls free().
*/
char * get_adjacents(const graph_ptr_t g, char vertex, unsigned int *return_size) {
    int i = get_index(g, vertex);
    unsigned int degree = get_degree(g, vertex);
    *return_size = degree;
    char *result = (char *)malloc(sizeof(char) * degree);
    if (result == NULL) exit(EXIT_FAILURE);
    if (degree == 0 || i == -1) return result;

    unsigned int adjacent_index = 0;
    adjacent_ptr_t p = g->vexs[i]->first_adjacent;
    while (p) {
        result[adjacent_index++] = g->vexs[p->index]->data;
        p = p->next;
    }

    return result;
}


void destroy(graph_ptr_t g) {
    for (unsigned int i=0; i<g->vertexs; i++) {
        adjacent_ptr_t p = g->vexs[i]->first_adjacent, q;
        while (p) {
            q = p->next;
            free(p);
            p = q;
        }
        free(g->vexs[i]);
    }
}


int main(void) {
    graph_t graph;
    init(&graph, DEFAULT_INITIAL_CAPACITY);
    /*
    A -> 3
    B -> 2 -> 0
    C -> 1 -> 0
    D
    */
    construct(&graph, DEFAULT_INITIAL_CAPACITY);
    has_arc(&graph, 'A', 'D');
    has_arc(&graph, 'D', 'A');
    get_degree(&graph, 'B');
    unsigned int return_size;
    char *p = get_adjacents(&graph, 'C', &return_size);
    for (unsigned int i=0; i<return_size; i++) {
        printf("%c\n", p[i]);
    }
    free(p);
    destroy(&graph);
    return 0;
}
