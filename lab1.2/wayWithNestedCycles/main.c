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
            r *= (sin(j)); // <=, ++, jump, sin(), *=,    - 5
            count += 5;
        }
        s += (sin(i) +2) / (i + r); // <=, ++, jump, =, =, +=, sin(), +, /, +
        count += 10;
    }
    count += 2; // 2
    printf("%d \n",count);
    printf("%.7lf",s);
    return 0;
}