#ifndef MATRIX_H
#define MATRIX_H

#define NUM_VERTICES 11
#define RADIUS 16
#define SEED 3215
#define K 0.705

double **directedMatrix();
double **undirectedMatrix();
void freeMatrix(double**);
void freeCoords(int**);
void outputMatrix(double**);
#endif