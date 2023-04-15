#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Первые функции
double g_x1(double x, int equation) {
    switch (equation) {
    case 1:
        return sqrt(5 * sin(x));
    case 2:
        return sin(x) + 0.15;
    case 3:
        return sqrt(sqrt(9 + x) - x + 4);
    default:
        printf("\nОшибка\n");
        return 0;
    }
}
double g_x1_derivative(double x, int equation) {
    switch (equation) {
    case 1:
        return fabs((5 * cos(x)) / (2 * sqrt(5 * sin(x))));
    case 2:
        return fabs(cos(x));
    case 3:
        return fabs((1 / (2 * sqrt(9 + x)) - 1) /
                    (2 * sqrt(sqrt(9 + x) - x + 4)));
    default:
        printf("\nОшибка\n");
        return 0;
    }
}

// Вторые функции
double g_x2(double x, int equation) {
    switch (equation) {
    case 1:
        return asin((x * x) / 5);
    case 2:
        return sin(x) + 0.15;
    case 3:
        return -sqrt(sqrt(9 + x) - x + 4);
    default:
        printf("\nОшибка\n");
        return 0;
    }
}
double g_x2_derivative(double x, int equation) {
    switch (equation) {
    case 1:
        return fabs((2 * x) / sqrt(25 - pow(x, 4)));
    case 2:
        return fabs(cos(x));
    case 3:
        return fabs((1 / (2 * sqrt(9 + x)) - 1) /
                    (2 * sqrt(sqrt(9 + x) - x + 4)));
    default:
        printf("\nОшибка\n");
        return 0;
    }
}

int main() {
    system("chcp 65001");

    int equation = 0;
    printf("Уравнения:\n");
    printf("(1) x^2 - 5sin(x) = 0\n");
    printf("(2) sin(x) - x + 0.15 = 0\n");
    printf("(3) x - (9 + x)^(1/2) + x^2 - 4 = 0\n");
    printf("Напишите номер уравнения: ");
    scanf("%d", &equation);
    printf("\n");

    double e = 0;
    printf("Введите точность e: ");
    scanf("%lf", &e);
    printf("\n");

    // Первый x
    printf("Вычисление x1:\n");
    double x = 1.57;
    double x_last = g_x1(x, equation);
    printf("Первое приближение: %lf\n", x);
    // Проверка на сходимость
    if (g_x1_derivative(x, equation) >= 1) {
        printf("Не сходится.........\n");
        return 1;
    }

    while (fabs(x - x_last) >= e) {
        x_last = x;
        x = g_x1(x_last, equation);
        printf("x[n], x[n + 1] = %lf, %lf\n", x_last, x);
    }

    printf("x1: %lf\n", x);

    if (equation == 2)
        return 0;

    // Второй x
    printf("Вычисление x2:\n");
    x = 1.57;
    x_last = g_x2(x, equation);
    printf("Первое приближение: %lf\n", x);
    // Проверка на сходимость
    if (g_x2_derivative(x, equation) >= 1) {
        printf("Не сходится.........\n");
        return 0;
    }

    while (fabs(x - x_last) >= e) {
        x_last = x;
        x = g_x2(x_last, equation);
        printf("x[n], x[n + 1] = %lf, %lf\n", x_last, x);
    }

    printf("x2: %lf\n", x);
    return 0;
}
