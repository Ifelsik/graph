#include "../include/graph.h"
#include "../include/file.h"

tVertex* setVertex(tVertex *vertex_p, int id, tEdge *adjacent_edge) {
    int vertex_has_loop = 0;
    vertex_p->id = id;
    for (int i = 0; i < vertex_p->adjacent_edges_num; i++) {
        if (vertex_p->adjacent_edges[i] == adjacent_edge) {
            vertex_has_loop = 1;
            break;
        }
    }
    if (!vertex_has_loop) {
        vertex_p->adjacent_edges[vertex_p->adjacent_edges_num] = adjacent_edge;
        vertex_p->adjacent_edges_num++;
    }
    return vertex_p;
}

tEdge* setEdge(tEdge *edge_p, int id, int weight, tVertex *vert1, tVertex *vert2) {
    edge_p->id = id;
    edge_p->weight = weight;
    edge_p->vertex_1 = vert1;
    edge_p->vertex_2 = vert2;
    return edge_p;
}

tVertex* find_vertex_by_id(tGraph *graph_p, int id) {
    for (int i = 0; i < graph_p->vertices_n; i++) {
        if (graph_p->vertices[i]->id == id)
            return graph_p->vertices[i];
    }
    return NULL;
}


/*
@brief Initialization of Graph.
@param graph_p: pointer on graph
@param vertices_n: number of vertices
@param edges_n: number of edges
*/
tGraph* initializeGraph(int vertices_n, int edges_n) {
    tGraph *graph_p = (tGraph*) malloc(sizeof(tGraph));
    graph_p->vertices_n = vertices_n;
    graph_p->edges_n = edges_n;

    graph_p->vertices = (tVertex**) malloc(sizeof(tVertex*) * vertices_n);
    graph_p->edges = (tEdge**) malloc(sizeof(tEdge*) * edges_n);

    for (int i = 0; i < vertices_n; i++) {
        graph_p->vertices[i] = (tVertex*) malloc(sizeof(tVertex));
        graph_p->vertices[i]->adjacent_edges = (tEdge**) malloc(sizeof(tEdge*) * edges_n);
        graph_p->vertices[i]->id = 0;
        graph_p->vertices[i]->adjacent_edges_num = 0;
    }

    for (int i = 0; i < edges_n; i++) {
        graph_p->edges[i] = (tEdge*) malloc(sizeof(tEdge));
        graph_p->edges[i]->id = 0;
        graph_p->edges[i]->weight = 0;
    }
    
    return graph_p;
};


tGraph* createGraph(tGraph *graph_p, int **matrix) {
    int matrix_size = graph_p->vertices_n;
    int edge_id = 0;
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j <= i; j++) {
            if (matrix[i][j] != 0) {
                tEdge *edge = NULL;
                edge = setEdge(graph_p->edges[edge_id], edge_id,
                       matrix[i][j], graph_p->vertices[i], graph_p->vertices[j]);
                graph_p->edges[edge_id] = edge;
                graph_p->vertices[i] = setVertex(graph_p->vertices[i], i, edge);
                graph_p->vertices[j] = setVertex(graph_p->vertices[j], j, edge);
                edge_id++;
            }
        }
    }
    return graph_p;
}


void delGraph(tGraph** graph_p) {
    for (int i = 0; i < (*graph_p)->vertices_n; i++) {
        free((*graph_p)->vertices[i]->adjacent_edges);
        free((*graph_p)->vertices[i]);
    }
    for (int i = 0; i < (*graph_p)->edges_n; i++) {
        free((*graph_p)->edges[i]);
    }
    free(*graph_p);
}

void showGraph(tGraph* graph_p) {
    FILE *file_p = NULL;
    char *template = NULL;
    template = readFile("./files/dot_template.txt", template);

    file_p = fopen("./graph.txt", "w");
    assert(file_p != NULL);
    fputs(template, file_p);

    for (int i = 0; i < graph_p->edges_n; i++) {
        int left_vertex_id = 0;
        int right_vertex_id = 0;
        float weight = 0;
        left_vertex_id = graph_p->edges[i]->vertex_1->id;
        right_vertex_id = graph_p->edges[i]->vertex_2->id;
        weight = (float) graph_p->edges[i]->weight;
        fprintf(file_p, "%d -- %d[label=\"%.2f\"]\n", left_vertex_id, right_vertex_id, weight); 
    }
    fputc('}', file_p);

    fclose(file_p);

    system("dot -Tpng > graph_visualization.png < graph.txt");
}
