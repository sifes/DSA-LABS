#include <stdio.h>
double multiply (int i,double x) {
    return x*x*(2*i-1)/(2*i+1);
}
double loop(double x, int amount) {
    double sum = x;
    double current = x;
    for (int i = 2; i <= amount ; i++) {
        current *= -multiply(i-1,x);
        sum += current;
    }
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
        double sum = loop(x,n);
        printf("Result: %.10lf\n", sum);
    }

    return 0;
}
