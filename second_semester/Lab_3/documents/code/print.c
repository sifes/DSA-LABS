#include <stdio.h>
#include "./header/matrix.h"

int main() {
    double **directed = directedMatrix();
    double **undirected = undirectedMatrix();

    printf("\nDirected Graph Matrix");
    outputMatrix(directed);
    freeMatrix(directed);

    printf("\nUndirected Graph Matrix");
    outputMatrix(undirected);
    freeMatrix(undirected);
}