#include <stdio.h>
double multiply (int i, double x) {
    return x*x*(2*i-1)/(2*i+1);
}
double recursion(double previous, int i, double sum, double x, unsigned int n) {
    double current;
    if (i == 1) {
        current = x;
    } else {
        current = -previous * multiply(i-1,x);
    }
    sum += current;
    if (i == n) {
        return sum;
    } else {
        return recursion(current,i+1, sum, x, n);
    }
}
double provideRecursion ( double x, int n) {
    return recursion(0,1,0,x,n);
}
int main() {
    double x;
    unsigned int n;
    printf("enter x (hint: it must be |x| < 1) = ");
    scanf("%lf", &x);
    if(x >= 1 || x <=-1) {
        printf("x must be |x| < 1");
    } else {
        printf("enter n = ");
        scanf("%d", &n);
        double result = provideRecursion(x,n);
        printf("Result: %lf\n", result);
    }
    return 0;
}