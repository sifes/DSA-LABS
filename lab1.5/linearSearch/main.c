#include <stdio.h>

int main() {
    int x;
    int arr[8][9] = {
            {12, 9, 8, 21, 44, 2, 49, 18, 6},
            {31, 12, 11, 5, 26, 42, 39, 19, 28},
            {1, 7, 12, 14, 9, 36, 20, 50, 4},
            {31, 16, 37, 12, 13, 45, 10, 27, 23},
            {38, 22, 25, 33, 12, 29, 43, 24, 17},
            {48, 32, 34, 40, 41, 12, 19, 3, 8},
            {2, 9, 45, 7, 14, 50, 28, 12, 39},
            {5, 20, 33, 49, 10, 26, 19, 44, 12}
    };

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%3d ", arr[i][j]); // Adjust the format to align the elements properly
        }
        printf("\n"); // Move to the next row
    }
    int i, j;
    int isPresent = 0;
    printf("Enter x: ");
    scanf("%d", &x);

    for (i = 0; i < 8; i++) {
        isPresent = 0;
        for (j = 0; j < 9; j++) {
            if(x == arr[i][j]) {
                printf("in %d row number %d is at %d index\n", i,x,j);
                isPresent = 1;
            }
        }
        if(isPresent==0) {
            printf("there are no number %d in the %d row\n", x,i);
        }
    }
    return 0;
}