#include <stdio.h>
#include <stdlib.h>

double recDescent(double x, int n, int i, double F, double sum) {
    if (n == 1) {
        sum = 1 + x/2;
    }
    if (i <= n) {
        sum += F;
        F = -1 * F * x * (2*i - 1) / (2 * (i + 1));
        sum = recDescent(x, n, i + 1, F, sum);
    }
    return sum;
}

double recReturn(double x, int n, int i, double F, double sum) {
    if (i <= n) {
        sum += F;
        F = -1 * F * x * (2*i - 1) / (2 * (i + 1));
        return recReturn(x, n, i + 1, F, sum);
    }
    return sum;
}

double recMixed(double x, int n, int i, double F) {
    printf("%d\n", n);

    if (n == 0) {
        F = 1;
    }
    else if(n>1) {
        F = -1 * F * x * (2*i - 1) / (2 * (i + 1));
        F += recMixed(x, n-1, i + 1, F);
    }
    else {
        F = 1 + x/2;
    }
    return F;
}

double loop(double x, int n, double F, double sum) {
    for (int i = 1; i <= n; i++) {
        sum += F;
        printf("%f\n", F);
        F = -1 * F * x * (2*i - 1) / (2 * (i + 1));
    }
    return sum;
}

int main() {
    double x;
    int n;

    printf("Enter x: ");
    scanf("%lf", &x);
    printf("Enter n: ");
    scanf("%d", &n);

    if (x >= 1) {
        printf("|x| should be less than 1\n");
        return 1;
    }

    printf("Descent recursion result: %lf\n", recDescent(x, n, 1, x/2, 1));
    printf("Return recursion result: %lf\n", recReturn(x, n, 1, x/2, 1));
    printf("Mixed recursion result: %lf\n", recMixed(x, n, 1, x/2));
    printf("Loop result: %lf", loop(x, n, x/2, 1));
    return 0;
}
