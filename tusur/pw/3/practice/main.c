#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double recursive(double x, int n, int i) {
    if (n == i)
        return x;
    return x - recursive(x * pow(x, 1.0 / i) / (i + 1), n, i + 1);
}

double ln(double x, int n) {
    int i = 1;
    return recursive(x, n, i);
}

int run() {
    double x = 0;
    int n = 0;
    printf("Введите значение x и точность n (x n): ");
    scanf("%lf %d", &x, &n);
    printf("\n");

    printf("ln(%lf + 1) с точностью до %d: %lf", x, n, ln(x, n));
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
#ifdef _WIN32
    system("chcp 65001");
#endif

    if (run() == EXIT_FAILURE)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
