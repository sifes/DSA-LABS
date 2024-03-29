#include <stdlib.h>
#include <stdio.h>

#define NUM_VERTICES 11
#define SEED 3215
#define K 0.705

double **randm() {
    int n = NUM_VERTICES;
    srand(SEED);
    double **matrix = (double **) malloc(sizeof(double *) * n);
    for (int i = 0; i < n; i++) {
        matrix[i] = (double *) malloc(sizeof(double) * n);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = (double) (rand() * 2.0) / (double) RAND_MAX;
        }
    }
    return matrix;

}

double **mulmr(double **matrix) {
    int n = NUM_VERTICES;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] *= K;
            matrix[i][j] = matrix[i][j] < 1 ? 0 : 1;
        }
    }
    return matrix;
}

void freeMatrix(double **matrix) {  // звільнення пам'яті від матриці
    int n = NUM_VERTICES;
    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);
}

void freeCoords(int **coords) {  // звільнення пам'яті від координат
    for (int i = 0; i < 2; i++) free(coords[i]);
    free(coords);
}

double **directedMatrix() { // генерація матриці орієнтованого графа
    double **T = randm();
    double **A = mulmr(T);
    return A;
}

double **undirectedMatrix() { // генерація матриці неорієнтованого графа
    int n = NUM_VERTICES;
    double **A = directedMatrix();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j]) A[j][i] = 1;
        }
    }
    return A;
}

void outputMatrix(double **matrix) {
    int n = NUM_VERTICES;
    for (int i = 0; i < n; i++) {
        printf("\n");
        for (int j = 0; j < n; j++) {
            printf("%.0lf  ", matrix[i][j]);
        }
    }
    printf("\n");
}
