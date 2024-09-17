#ifndef MATRIX_H
#define MATRIX_H

#define NUM_VERTICES 11
#define RADIUS 16
#define SEED 3215
#define K 0.64
#define K2 0.7

double **directedMatrix();
double **undirectedMatrix();
void freeMatrix(double**);
void freeCoords(int**);
void outputMatrix(double**);
void printDegrees(double**);

int *degrees(double**);
int *halfDegreeIn(double**);
int *halfDegreeOut(double**);
int *sumHalfDegrees(const int*,const int*);
int isRegular(const int*);

int *findIsolatedVert(const int*);
int *findTerminalVert(const int*);
double **multiplyMatrices(double**, double**);
double **reachabilityMatrix(double**);
double **connectivityMatrix(double**);
double **components(double**);
void condensationAdjacency(double**);
double **condensationAdjacencyByK(double);
double **formatMatrix(double**);

#endif