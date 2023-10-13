#include <stdio.h>
#include <math.h>

int main() {
    int n, i, j; double s, r;
    printf("Enter n: \n");
    scanf("%d", &n);
    i = 1; j = 1; s = 0;
    for (i = 1; i <= n; i++) {
        r = 1;
        for ( j = 1; j <= i; j++) {
            r *= (sin(j)); // <=, ++, sin(), *=, jump   - 5
        }
        s += (sin(i) +2) / (i + r); //  <=, ++, sin(), +, +, /, +=,  =, =, jump   - 10
    }
    // 3
    printf("%.7lf",s);
    return 0;
}