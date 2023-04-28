#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
The default initial capacity - MUST be a power of two.
*/
#define DEFAULT_INITIAL_CAPACITY (1 << 3)

#define SUCCESS 0
#define FAILURE -1

typedef struct {
    /* vertex table*/
    char vexs[DEFAULT_INITIAL_CAPACITY];
    /* adjacency matrix（edge table）*/
    int arc[DEFAULT_INITIAL_CAPACITY][DEFAULT_INITIAL_CAPACITY];
    /* number of vertex */
    unsigned int vertexs;
    /* number of edge */
    unsigned int edges;
} graph_t, *graph_ptr_t;


void init(graph_ptr_t g, int n) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            g->arc[i][j] = 0;
        }
    }
}


int construct(graph_ptr_t g, unsigned int n) {
    // unsigned int vertexs, edges;
    printf("Please input number of vertex & edge: \n");
    scanf("%d %d", &g->vertexs, &g->edges);
    if (g->vertexs < 1 || g->vertexs > n) return FAILURE;

    unsigned int type;
    printf("Please input graph type, 0 - undirected graphs, 1 - directed graphs\n");
    scanf("%d", &type);
    if (type == 0 && g->edges > (g->vertexs * (g->vertexs - 1)) / 2) return FAILURE;
    if (type == 1 && g->edges > g->vertexs * (g->vertexs - 1)) return FAILURE;

    /* construct vertex table */
    for (unsigned int i=0; i<g->vertexs; i++) {
        scanf("\n%c", &g->vexs[i]);
        getchar();
    }

    /*
    construct edge table
    undirected graphs for example
    */
    for (unsigned int k=0; k<g->edges; k++) {
        unsigned int i, j;
        printf("Please input edge (i, j)\n");
        scanf("%d %d", &i, &j);
        if (i > g->vertexs - 1) return FAILURE;
        if (j > g->vertexs - 1) return FAILURE;
        g->arc[i][j] = g->arc[j][i] = 1;
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
        if (g->vexs[i] == vertex) {
            index = i;
            break;
        }
    }

    return index;
}


/*
:param v1: element of g->vexs
:param v2: element of g->vexs

:return: true if vertex v1 & v2 has edge
*/
bool has_edge(const graph_ptr_t g, char v1, char v2) {
    int i = get_index(g, v1);
    int j = get_index(g, v2);
    if (i == -1 || j == -1) return false;
    return g->arc[i][j] == 1 ? true : false;
}


/*
:param vertex: index of g->vexs

:return: vertex's degree
*/
unsigned int get_degree(const graph_ptr_t g, char vertex) {
    unsigned int degree = 0;
    int i = get_index(g, vertex);
    if (i == -1) return degree;

    for (unsigned int j=0; j<g->vertexs; j++) {
        degree += g->arc[i][j];
    }

    return degree;
}


/*
:param vertex: index of g->vexs

:return: vertex's adjacents

Note: The returned array must be malloced, assume caller calls free().
*/
char * get_adjacents(const graph_ptr_t g, char vertex, unsigned int *return_size) {
    int i = get_index(g, vertex);
    unsigned int degree = get_degree(g, vertex);
    *return_size = degree;
    char *result = (char *)malloc(sizeof(char) * degree);
    if (degree == 0 || i == -1) return result;

    unsigned int adjacent_index = 0;
    for (unsigned int j=0; j<g->vertexs; j++) {
        if (g->arc[i][j] == 1) {
            result[adjacent_index++] = g->vexs[j];
        }
    }

    return result;
}


int main(void) {
    graph_t graph;
    init(&graph, DEFAULT_INITIAL_CAPACITY);
    /*
    vertex[] = {'A', 'B', 'C', 'D'}
    arc[][4] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0},
    }
    */
    construct(&graph, DEFAULT_INITIAL_CAPACITY);
    has_edge(&graph, 'A', 'C');
    get_degree(&graph, 'B');
    unsigned int return_size;
    char *q = get_adjacents(&graph, 'B', &return_size);
    for (unsigned int i=0; i<return_size; i++) {
        printf("%c\n", q[i]);
    }
    free(q);
    return 0;
}
