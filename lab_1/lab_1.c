#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define PI          3.14159
#define SQRT_5      2.23606798

#define MIN_ARG     0
#define MAX_ARG     1
#define EPS         1e-2


double func(double arg)
{
    return arg * arg * arg - arg;
}


double fib(uint32_t n)
{
    return (double)((pow((1 + SQRT_5) / 2, n) - pow((1 - SQRT_5) / 2, n)) / SQRT_5);
}

double fib_min(double (*foo)(double), double a, double b, double eps)
{
    double x_1, x_2;

    uint32_t n = 1;
    double f_x1, f_x2;
    uint16_t k = 0;
    double _x_1;
    double _a = a;
    double _b = b;

    while (((b - a) / EPS) >= fib(n))
        n++;

    printf("F(%d) = %f\n", n-1, fib(n-1));
    printf("F(%d) = %f\n", n, fib(n));
    printf("F(%d) = %f\n", n+1, fib(n+1));
    x_1 = a + ( b - a ) * fib(n - 2) / fib(n);
    x_2 = a + ( b - a ) * fib(n - 1) / fib(n);

    f_x1 = foo(x_1);
    f_x2 = foo(x_2);

    printf("****************\n");
    printf("ITERATION_%d\n", k);
    printf("a = %f\n", a);
    printf("b = %f\n", b);
    printf("x1 = %f\n", x_1);
    printf("f(x1) = %f\n", f_x1);
    printf("x2 = %f\n", x_2);
    printf("f(x2) = %f\n", f_x2);

    while (sqrt(b*b - a*a) >= EPS && k < n) {

        k++;

        _x_1 = x_1;
        _a = a;
        _b = b;

        if (f_x1 <= f_x2) {
            b = x_2;
            x_2 = x_1;
            f_x2 = f_x1;
            x_1 = a + ( b - a ) * (fib(n - k - 2) / fib(n - k));
            f_x1 = foo(x_1);
        } else {
            a = x_1;
            x_1 = x_2;
            f_x1 = f_x2;
            x_2 = a + ( b - a ) * (fib(n - k - 1) / fib(n - k));
            f_x2 = foo(x_2);
        }
    

        if (k == n - 2) {

            x_1 = _x_1;
            f_x1 = foo(x_1);

            x_2 = x_1 + EPS;

            f_x2 = foo(x_2);

            if (f_x2 == f_x1) {
                a = x_1;
                b = _b;
            }
            else if (f_x1 < f_x2) {
                a = _a;
                b = x_2;
            }

            break;
        }

        printf("****************\n");
        printf("ITERATION_%d\n", k);
        printf("a = %f\n", a);
        printf("b = %f\n", b);
        printf("x1 = %f\n", x_1);
        printf("f(x1) = %f\n", f_x1);
        printf("x2 = %f\n", x_2);
        printf("f(x2) = %f\n", f_x2);
    }

    return (a + b) / 2;
}

int main(void)
{


    FILE *f = fopen("data.txt", "w");

    for(double i = MIN_ARG; i <= MAX_ARG; i = i + EPS)
        fprintf(f, "%f\t%f\n", i, func(i));

    fclose(f);


    printf("FIBONACHI\n");
    printf("x = %f\n", fib_min(func, MIN_ARG, MAX_ARG, EPS));

    return 0;
}
