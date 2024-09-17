#include <stdio.h>
#include "./header/matrix.h"

int main() {
    double **directed = directedMatrix();
    double **undirected = undirectedMatrix();

    printf("\nDirected Graph Matrix");
    outputMatrix(directed);

    printf("\nUndirected Graph Matrix");
    outputMatrix(undirected);

    printf("\n1. Degrees of vertices of the undirected graph");
    int *degreesUndirected = degrees(undirected);
    printDegrees(degreesUndirected);
    freeMatrix(degreesUndirected);

    printf("\n1. Degrees of vertices of the directed graph");
    int *degreesDirected = degrees(directed);
    printDegrees(degreesDirected);
    freeMatrix(degreesDirected);

    printf("\n2. Outdegrees of vertices of the directed graph");
    int *halfOut = halfDegreeOut(directed);
    printDegrees(halfOut);
    printf("\n2. Indegrees of vertices of the directed graph");
    int *halfIn = halfDegreeIn(directed);
    printDegrees(halfIn);

    printf("\n3. Is graph a regular: ");
    int *sumDegrees = sumHalfDegrees(halfOut, halfIn);
    freeMatrix(halfOut);
    freeMatrix(halfIn);
    if (isRegular(sumDegrees)) printf("%d\n", sumDegrees[0]);
    else printf("irregular\n");

    printf("\n4. Vertices (enumeration)\n");
    int *isolatedVertices = findIsolatedVert(sumDegrees);
    int *pendantVertices = findTerminalVert(sumDegrees);

    printf("Isolated: ");
    if (isolatedVertices[0]) printDegrees(isolatedVertices);
    else printf("none\n");

    printf("Pendant: ");
    if (pendantVertices[0]) printDegrees(pendantVertices);
    else printf("none\n");

    freeMatrix(pendantVertices);
    freeMatrix(isolatedVertices);

    freeMatrix(directed);

    freeMatrix(undirected);

}