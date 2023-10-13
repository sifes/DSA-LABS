#include <stdio.h>
#include <math.h>

int main() {
    int n, i; double s, r;
    printf("Enter n: \n");
    scanf("%d", &n);
    i = 1; s = 0; r = 1;
    for (i = 1; i <= n; i++) {
        r *= sin(i);
        s += (sin(i) +2) / ( i+ r);
        // *=, sin(), +=, sin(), +, +, /, <=, ++, jump
    }
    // 4 операції присвоєння
    printf("%.7lf",s);
    return 0;
}
