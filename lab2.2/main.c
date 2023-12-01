#include <stdio.h>

int main() {
    int n = 8;
    int i, j;
    int Array[8][8] = {
            {81 ,61 ,51, 61, 51, 12, 11, 1252},
            {91, 21, 21, 11, 14, 13, 5352, 13},
            {61, 35, 25, 13, 14, 1231 ,21, 23},
            {91, 41, 11, 13, 2323, 51, 21, 15},
            {91, 23, 21, 7567, 14, 51, 21, 13},
            {61, 43, 2342, 1, 11, 31, 31, 19},
            {32, 5232, 81, 14, 15, 11, 11, 18},
            {1243, 11, 17, 31, 19, 51, 15, 17},
    };
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            printf("%d ", Array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int current;
    for (i = 1; i < n; i++) {
        current = Array[(n-1)-i][i];
        j = 0;
        while (Array[(n-1)-j][j] < current) {
            j++;
        }
        for (int k = i-1; k >= j; k--) {
            Array[(n-1)-k -1][k + 1] = Array[(n-1)-k][k];
        }
        Array[(n-1)-j][j] = current;
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            printf("%d ", Array[i][j]);
        }
        printf("\n");
    }
    return 0;
}
