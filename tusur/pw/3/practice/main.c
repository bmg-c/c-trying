#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double iterational(double x, int n)
{
    double elem = x;
    double sum = elem; 
    
    for (int i = 2; i != n; i++)
    {
        elem = - (elem * x) / i;
        sum += elem;

        printf("%lf\n", elem);
    }

    return sum;
}

double recursive(double x, double prev, int n, int i)
{
    double next = prev * x / i;
    printf("%lf\n", next);

    if (n == i)
        return next;
    return next - recursive(x, next, n, i + 1);
}

double ln(double x, int n)
{
    return recursive(x, 1, n, 1);
}

int main ()
{
    double x = 0; int n = 0;

    printf("Введите х и n-ый член: ");
    scanf("%lf%d", &x, &n);

    printf("Не рекурентная функция: %lf\n\n", iterational(x, n));
    printf("Результат: %lf\n", ln(x, n));
    printf("\nРезультат log(x + 1): %lf", log(1 + x));


}
