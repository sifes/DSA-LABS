#include <stdio.h>

int main() {
    int x;
    int arr[8][9] = {
            {12, 12, 8, 21, 44, 2, 49, 18, 6},
            {31, 47, 11, 5, 26, 42, 39, 19, 28},
            {1, 7, 46, 14, 9, 36, 20, 50, 4},
            {31, 16, 37, 3, 13, 45, 10, 27, 23},
            {38, 22, 25, 33, 15, 29, 43, 24, 17},
            {48, 32, 34, 40, 41, 0, 19, 3, 8},
            {2, 9, 45, 7, 14, 50, 28, 16, 39},
            {5, 20, 33, 49, 10, 26, 19, 44, 30}
    };
    int i, j;
    int col = -1, row= -1;
    printf("Enter x: ");
    scanf("%d", &x);

    for (i = 0; i < 8 && row == -1; i++) {
        for (j = 0; j < 9; j++) {
            if(x == arr[i][j]) {
                col = j;
                row = i;
                break;
            }
        }
    }

    if (row == -1) {
         printf("the %d is not present matrix\n",x);
    } else {
        printf("the %d is at [%d][%d] index\n",x, row, col);
    }
    return 0;
}