#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct sVertex {
    int id;
    int adjacent_edges_num;
    struct sEdge **adjacent_edges;
} tVertex;

typedef struct sEdge {
    int id;
    int weight;
    tVertex *vertex_1;
    tVertex *vertex_2;
} tEdge;

typedef struct sGraph {
    tVertex **vertices;
    tEdge **edges;
    int vertices_n;
    int edges_n;
} tGraph;

tGraph* initializeGraph(int vertices_n, int edges_n);

tVertex* setVertex(tVertex *vertex_p, int id, tEdge *adj_edge);

tEdge* setEdge(tEdge *edge_p, int id, int weight, tVertex *vert1, tVertex *vert2);

tGraph* createGraph(tGraph *graph_p, int **matrix);

void delGraph(tGraph** graph_p);

void showGraph(tGraph* graph_p);

#endif
