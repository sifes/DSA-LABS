#include <stdio.h>
double multiply (int i,double x) {
    return x*x*(2*i-1)/(2*i+1);
}
double recursion (double previous, int i, double x, int n) {
    double current;
    if (i == 1) {
        current = x;
    } else {
        current = -previous * multiply(i-1, x);
    }
    if (i == n) {
        return current;
    } else {
        double sum = current + recursion(current,i+1, x, n);
        return sum;
    }
}
double provideRecursion (double parameter, int amount) {
    return recursion(0,1,parameter,amount);
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
        double sum = provideRecursion(x,n);
        printf("Result: %.10lf\n", sum);
    }
    return 0;
}
