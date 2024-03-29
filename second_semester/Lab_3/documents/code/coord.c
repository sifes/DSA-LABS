#include <stdlib.h>
#include "../header/matrix.h"
#include <stdio.h>

int **getVerticesCoords(int start) {
    int n = NUM_VERTICES;
    int vertInSide = (int)(n / 3.0 + 0.5) + 1;
    int **coords;
    coords = malloc(n * 2 * sizeof(size_t*));
    for (int i = 0; i < 2; i++) {
        coords[i] = malloc(n * sizeof(int));
    }

    int distance = 100;
    int distanceAtDown;
    if (n%3 == 0) {
        distanceAtDown = distance*2;
    } else if (n%3 == 1) {
        distanceAtDown = (vertInSide-1)*2*distance / vertInSide;
    } else {
        distanceAtDown = (vertInSide-1)*2*distance / (vertInSide-2);
    }

    int tempX = start;
    int tempY = start;
    for (int j = 0; j < vertInSide; j++) {
        tempX += distance;
        tempY += distance;
        coords[0][j] = tempX;
        coords[1][j] = tempY;
    }

    for (int j = vertInSide; j < vertInSide*2-1; j++) {
        tempX += distance;
        tempY -= distance;
        coords[0][j] = tempX;
        coords[1][j] = tempY;
    }

    for (int j = vertInSide*2-1; j < n; j++) {
        tempX -= distanceAtDown;
        coords[0][j] = tempX;
        coords[1][j] = tempY;
    }

    return coords;
}
