#include <stdio.h>
int main() {
    int n; float x, res, val;
    printf("Enter n: \n");
    scanf("%d", &n);
    printf("Enter x: \n");
    scanf("%f", &x);
    val = 1; res = 0;
    if (0 < x && x <2) {
        for (int i = 1; i <= n; i++) {
            val *= (x-1);
            if (i & 1) {
                res += val / i;
            } else {
                res -= val / i;
            }
        }
        printf("the res: %.7lf\n",res);
    } else {
        printf("x must be greater than 0 and lower than 2");
    }
    return 0;
}
