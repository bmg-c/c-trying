#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double f1(double x) { return 0.1 * pow(x, 2) - x * log(x); }

double f2(double x) {
    return pow(x, 4) - 26 * pow(x, 3) + 131 * pow(x, 2) + 226 * x + 120;
}

double f3(double x) { return 0.1 * sin(x) + pow(x, 3) - 1; }

void main1() {
    double e = 0;
    printf("Введите точность e: ");
    scanf("%lf", &e);

    double *x = (double *)malloc(sizeof(double) * 2);
    x[0] = 0.1;
    x[1] = x[0] + 1;

    while (fabs(x[0] - x[1]) >= e) {
        double temp = x[1];
        x[1] = x[1] - (f1(x[1]) * (x[1] - x[0])) / (f1(x[1]) - f1(x[0]));
        x[0] = temp;
    }

    printf("%lf", x[1]);
}

void main2() {
    double e = 0;
    printf("Введите точность e: ");
    scanf("%lf", &e);

    double *x = (double *)malloc(sizeof(double) * 2);
    x[0] = 0.1;
    x[1] = x[0] + e * 2;

    while (fabs(x[0] - x[1]) >= e) {
        double temp = x[1];
        x[1] = x[1] - (f2(x[1]) * (x[1] - x[0])) / (f2(x[1]) - f2(x[0]));
        x[0] = temp;
    }

    printf("%lf", x[1]);
}

void main3() {
    double e = 0;
    printf("Введите точность e: ");
    scanf("%lf", &e);

    double *x = (double *)malloc(sizeof(double) * 2);
    x[0] = 0.1;
    x[1] = x[0] + e * 2;

    while (fabs(x[0] - x[1]) >= e) {
        double temp = x[1];
        x[1] = x[1] - (f3(x[1]) * (x[1] - x[0])) / (f3(x[1]) - f3(x[0]));
        x[0] = temp;
    }

    printf("%lf", x[1]);
}

int run() {
    int equation = 0;
    printf("(1) 0,1 * x^2 - x * ln(x) = 0\n");
    printf("(2) x^4 - 26 * x^3 + 131 * x^2 - 226 * x + 120 = 0\n");
    printf("(3) 0,1 * sin(x) + x^3 - 1 = 0\n");
    printf("Напишите номер уравнения: ");
    scanf("%d", &equation);
    printf("\n");

    switch (equation) {
    case 1:
        main1();
        break;
    case 2:
        main2();
        break;
    case 3:
        main3();
        break;
    }

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
