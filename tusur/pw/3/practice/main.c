#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double factorial (double n)
{   
    if (n > 1)
        return n * factorial(n - 1);

    return 1;
}

double recursive(double x, int n, int i)
{
    double next = pow(x, i)/factorial(i);
    printf("%lf\n", next);

    if (n == i)
        return next;
    return next - recursive(x, n, i + 1);
}

double ln(double x, int n)
{
    return recursive(x + 1, n, 1);
}

int main ()
{
    double x = 0; int n = 0;

    printf("Введите х и n-ый член: ");
    scanf("%lf%d", &x, &n);

    x = ln(x, n);

    printf("Результат: %lf", x);

}
