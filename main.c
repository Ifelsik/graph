#include "./include/main.h"

int main() {
    char *path = "/home/misha_che/C/flita2/files/test.txt";
    char **lines = NULL;
    int **matrix = NULL;
    int matrix_size = 0;
    int vertices_number = 0;
    int edges_number = 0;

    tGraph *graph = NULL;


    int res1 = 0;
    int res2 = 0;
    
    res1 = readLinesFromFile(path, &lines);
    assert(res1 == 0);
    
    res2 = parseSquareMatrix(lines, &matrix);
    assert(res2 == 0);
    


/* DEBUG
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            printf("%d ", matrix[i][j]);
        }
        putchar('\n');
    }
*/
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
    showGraph(graph);
    
    return 0;
}
