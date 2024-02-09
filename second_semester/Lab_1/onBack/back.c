#include <stdio.h>
double multiply (int i, double x) {
    return x*x*(2*i-1)/(2*i+1);
}
double recursion(double x, int n, double *sum) {
    double current;
    if (n == 1) {
        current = x;
    } else {
        current = -recursion( x,n-1, sum) * multiply(n-1, x);
    }
    *sum += current;
    return current;
}
double provideRecursion ( double x, int n) {
    double sum = 0;
    recursion(x, n, &sum);
    return sum;
}
int main() {
    double x;
    int n;
    printf("enter x (hint: it must be |x| < 1) = ");
    scanf("%lf", &x);

    if(x >= 1 || x <=-1) {
        printf("x must be |x| < 1");
    } else {
        printf("enter n = ");
        scanf("%d", &n);
        printf("Result: %.10lf\n", provideRecursion(x, n));
    }

    return 0;
}
