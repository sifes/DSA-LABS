#include <stdio.h>

int main() {
    float x;
    float arr[8][9] = {
            {666, 666, 666, 6, 44, 2, 49, 18, 6},
            {666, 666, 666, 5, 26, 42, 39, 19, 28},
            {1, 7, 12, 14, 9, 36, 20, 50, 4},
            {31, 16, 37, 12, 13, 45, 10, 27, 23},
            {38, 22, 25, 33, 12, 29, 43, 24, 17},
            {48, 32, 34, 40, 41, 12, 19, 3, 8},
            {2, 9, 45, 7, 14, 50, 28, 12, 39},
            {5, 20, 33, 49, 10, 26, 19, 44, 9999}
    };

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%.2f ", arr[i][j]);
        }
        printf("\n");
    }
    int i, j;
    printf("Enter x: ");
    scanf("%f", &x);

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 9; j++) {
            if(x == arr[i][j]) {
                printf("number %.2f in %d row at %d index\n",x,i,j);
                return 0;
            }
        }
    }

    printf("there are no number %.2f in the array\n", x);
    return 0;
}