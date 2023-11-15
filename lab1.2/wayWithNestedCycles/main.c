#include <stdio.h>
#include <math.h>

int main() {
    int n, i, j, count; double s, r;
    printf("Enter n: \n");
    scanf("%d", &n);
    s = 0; count = 0;
    for (i = 1; i <= n; i++) {
        r = 1;
        for (j = 1; j <= i; j++) {
            r *= (sin(j));
            count += 5; // <=, ++, jump, sin(), *=
        }
        s += (sin(i) +2) / (i + r);
        count += 11;  // <=, <=, ++, jump, =, =, +=, sin(), +, /, +
    }
    count += 2; // операції присвоєння s = 0; i = 1;
    printf("%d \n",count);
    printf("%.7lf",s);
    return 0;
}