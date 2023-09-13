#include <stdio.h>

int main() {
    float x,y;
    printf("Enter x: \n");
    scanf("%f", &x);
    if (x<25)
    {
        if (x<=15 && x>5 || x<=-5 && x>-10)
        {
            y=x*x*x-6;
            printf("%.2f", y);
        }
        else
        {
            printf("no value");
        }
    }
    else
    {
        y = 2*x*x*x - 3*x +2;
        printf("%.2f", y);
    }
    return 0;
}