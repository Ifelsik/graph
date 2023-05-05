#include "./include/main.h"


int main() {
    char *path = "./files/test.txt";
    char **lines = NULL;
    int **matrix = NULL;
    int matrix_size = 0;
    int vertices_number = 0;
    int edges_number = 0;

    tGraph *graph = NULL;
    
    lines = readLinesFromFile(path);
    
    matrix = parseSquareMatrix(lines);
    
    
    matrix_size = getMatrixSize(lines);
    vertices_number = matrix_size;
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j <= i; j++) {
            if (matrix[i][j] != 0)
                edges_number++;
        }
    }

    graph = initializeGraph(vertices_number, edges_number);
    graph = createGraph(graph, matrix);

    bool *visited_vertices = (bool*) calloc(graph->vertices_n, sizeof(bool));
    dfsGraph(graph, 0, visited_vertices);
    if (isConnectedGraph(graph, visited_vertices)) {
        puts("Connected graph");
    } else {
        puts("Disconected graph");
    }
    
    showGraph(graph);

    free(visited_vertices);
    delGraph(&graph);
    return 0;
}
