#include <stdlib.h>
#include <stdio.h>
#include "./matrix.c"
#include "../header/matrix.h"

// степені вершин
int *degrees(double **matrix) {
    int n = NUM_VERTICES;
    int *vertexDegree;
    vertexDegree = malloc(n * sizeof(int));
    int counter;
    for (int i = 0; i < n; i++) {
        counter = 0;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] && i == j) counter += 2;
            else if (matrix[i][j]) counter++;
        }
        vertexDegree[i] = counter;
    }
    return vertexDegree;
}

// напівстепені виходу
int *halfDegreeOut(double **matrix) {
    int n = NUM_VERTICES;
    int *vertexDegree;
    vertexDegree = malloc(n * sizeof(int));
    int counter;
    for (int i = 0; i < n; i++) {
        counter = 0;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j]) counter++;
        }
        vertexDegree[i] = counter;
    }
    return vertexDegree;
}

// напівстепені входу
int *halfDegreeIn(double **matrix) {
    int n = NUM_VERTICES;
    int *vertexDegree;
    vertexDegree = malloc(n * sizeof(int));
    int counter;
    for (int j = 0; j < n; j++) {
        counter = 0;
        for (int i = 0; i < n; i++) {
            if (matrix[i][j]) counter++;
        }
        vertexDegree[j] = counter;
    }
    return vertexDegree;
}

// сума напівстепенів
int *sumHalfDegrees(const int *exit,const int *entry) {
    int n = NUM_VERTICES;
    int *vector;
    vector = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        vector[i] = exit[i] + entry[i];
    }
    return vector;
}

// регулярний граф чи ні
int isRegular(const int *degrees) {
    int n = NUM_VERTICES;
    int prev = degrees[0];
    for (int i = 1; i < n; i++) {
        if (degrees[i] != prev) return 0;
        prev = degrees[i];
    }
    return 1;
}

// ізольовані вершини
int *findIsolatedVert(const int *degrees) {
    int n = NUM_VERTICES;
    int *isolatedVert = calloc(n, sizeof(int));
    int counter = 0;
    isolatedVert[counter] = 0;
    for (int i = 0; i < n; i++) {
        if (degrees[i] == 0) isolatedVert[counter++] = i + 1;
    }
    return isolatedVert;
}

// висячі вершини
int *findTerminalVert(const int *degrees) {
    int n = NUM_VERTICES;
    int *terminalVert = calloc(n, sizeof(int));
    int counter = 0;
    terminalVert[counter] = 0;
    for (int i = 0; i < n; i++) {
        if (degrees[i] == 1) terminalVert[counter++] = i + 1;
    }
    return terminalVert;
}

// копіювання матриці
double **copyMatrix(double **matrix) {
    int n = NUM_VERTICES;
    double **copiedMatrix = (double **) malloc(sizeof(double *) * n);
    for (int i = 0; i < n; i++) {
        copiedMatrix[i] = malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            copiedMatrix[i][j] = matrix[i][j];
        }
    }
    return copiedMatrix;
}

// множення матриць
double **multiplyMatrices(double **first, double **second) {
    int n = NUM_VERTICES;
    double **multipliedMatrix = (double **) malloc(sizeof(double *) * n);
    for (int i = 0; i < n; i++) {
        multipliedMatrix[i] = malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            multipliedMatrix[i][j] = 0;
            for (int k = 0; k < n; k++) {
                multipliedMatrix[i][j] += first[i][k] * second[k][j];
            }
        }
    }
    return multipliedMatrix;
}

// додавання матриць
double **summMatrices(double **first, double **second) {
    int n = NUM_VERTICES;
    double **summedMatrix = (double **) malloc(sizeof(double *) * n);
    for (int i = 0; i < n; i++) {
        summedMatrix[i] = malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            summedMatrix[i][j] = first[i][j] + second[i][j];
        }
    }
    return summedMatrix;
}

// булеве перетворення
void booleanConversion(double **matrix) {
    int n = NUM_VERTICES;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j]) matrix[i][j] = 1;
        }
    }
}

// матриця досяжності
double **calcReachabilityMatrix(double **matrix) {
    const int n = NUM_VERTICES;
    double **copy = copyMatrix(matrix);
    double **sum = copy;
    double **prev = copy;
    double **tempPrev, **tempSum;

    for (int i = 1; i < n - 1; i++) {
        tempPrev = multiplyMatrices(prev, matrix);
        tempSum = summMatrices(sum, tempPrev);
        freeMatrix(sum);
        freeMatrix(prev);
        prev = tempPrev;
        sum = tempSum;
    }

    for (int i = 0; i < n; i++) {
        sum[i][i] += 1;
    }

    freeMatrix(prev);
    booleanConversion(sum);

    return sum;
}

// транспонування матриці
double **transposeMatrix(double **matrix) {
    int n = NUM_VERTICES;
    double **transposedMatrix = malloc(n * sizeof(size_t*));
    for (int i = 0; i < n; i++) {
        transposedMatrix[i] = malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            transposedMatrix[i][j] = matrix[j][i];
        }
    }
    return transposedMatrix;
}

// поелементне множення матриць
double **multiplyMatricesByElement(double **first, double **second) {
    int n = NUM_VERTICES;
    double **matrix = malloc(n * sizeof(size_t*));
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            matrix[i][j] = first[i][j] * second[i][j];
        }
    }
    return matrix;
}

// матриця зв'язності
double **getConnectivityMatrix(double **reachabilityMatrix) {
    double **transposedMatrix = transposeMatrix(reachabilityMatrix);
    double **strongConnectivityMatrix = multiplyMatricesByElement(reachabilityMatrix, transposedMatrix);
    freeMatrix(transposedMatrix);
    return strongConnectivityMatrix;
}

// пошук в глибину
void dfs(double **strongConnectivityMatrix, int startVert, double *component, int *visited) {
    visited[startVert] = 1;
    component[startVert] = 1;
    for (int adjacentVert = 0; adjacentVert < NUM_VERTICES; adjacentVert++) {
        if (!visited[adjacentVert] && strongConnectivityMatrix[startVert][adjacentVert]) {
            dfs(strongConnectivityMatrix, adjacentVert, component, visited);
        }
    }
}
void dfss(double** strongMatrix, int vert, int* visitedVert) {
    visitedVert[vert] = 1;

    for (int i = 0; i < NUM_VERTICES; ++i) {
        if (strongMatrix[vert][i] && !visitedVert[i]) {
            dfss(strongMatrix, i, visitedVert);
        }
    }
}

// компоненти сильної зв'язності
double **getComponents(double **strongConnectivityMatrix) {
    int n = NUM_VERTICES;
    int *visited = calloc(n, sizeof(int));

    double **components = calloc(n, sizeof(size_t*));
    for (int i = 0; i < n; i++) {
        components[i] = calloc(n, sizeof(double));
    }

    for (int vertex = 0; vertex < n; vertex++) {
        if (!visited[vertex]) {
            dfs(strongConnectivityMatrix, vertex, components[vertex], visited);
        }
    }

    free(visited);
    return components;
}

// визначити кількість вершин (для графа конденсації)
int getNumVertices(double **matrix) {
    int n = NUM_VERTICES;
    int count = 0;
    for (int row = 0; row < n; row++) {
        for (int j = 0; j < n; j++) {
            if (matrix[row][j]) {
                count++;
                row++;
            }
        }
    }
    return count;
}

// перетворення матриці для малювання графа конденсації
double **formatMatrix(double **components) {
    double **matrix = calloc(NUM_VERTICES, sizeof(size_t*));
    for (int i = 0; i < NUM_VERTICES; i++) {
        matrix[i] = calloc(NUM_VERTICES, sizeof(double));
    }

    for(int i = 0; i < NUM_VERTICES; i++) {
        if (!components[0][i]) matrix[1][i+1] = 1;
    }

    return matrix;
}

// матриця суміжності для графа конденсіції
void getCondensationAdjacency(double **components) {
    int numVertices = getNumVertices(components);

    double **matrix = calloc(numVertices, sizeof(size_t*));
    for (int i = 0; i < numVertices; i++) {
        matrix[i] = calloc(numVertices, sizeof(double));
    }

    int columns = 1;
    for (int i = 0; i < NUM_VERTICES; i++) {
        if (!components[0][i]) {
            matrix[0][columns] = 1;
            columns++;
        }
    }

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            printf("%.0lf  ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < numVertices; i++) free(matrix[i]);
    free(matrix);
}

// композиція для отримання компонентів по коефіцієнту
//double **getCondensationAdjacencyByK(double K) {
//    double **matrix = directedMatrix(K);
//    double **reachability = getReachabilityMatrix(matrix);
//    double **connectivity = getConnectivityMatrix(reachability);
//    double **components = getComponents(connectivity);
//
//    freeMatrix(matrix);
//    freeMatrix(reachability);
//    freeMatrix(connectivity);
//    return components;
//}