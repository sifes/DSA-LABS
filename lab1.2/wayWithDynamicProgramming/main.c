#include <stdio.h>
#include <math.h>

int main() {
    int n, i, count; double s, r;
    printf("Enter n: \n");
    scanf("%d", &n);
    s = 0; r = 1; count = 0;
    for (i = 1; i <= n; i++) {
        r *= sin(i);
        s += (sin(i) +2) / (i + r);
        count += 10; // <=, ++, jump, *=, sin(), +=, sin(), +, +, /
    }
    count += 3; // 3 операції присвоєння  i = 1; s = 0; r = 1;
    printf("%.7lf\n",s);
    printf("%d\n",count);
    return 0;
}
