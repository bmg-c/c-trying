#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Первое уравнение
// Выходная первая функция и ее производная для x1 (которая между 2 и 2.1)
double g1_x1(double x) { return sqrt(5 * sin(x)); }
double g1_x1_derivative(double x) {
    return fabs((5 * cos(x)) / (2 * sqrt(5 * sin(x))));
}
// Выходная вторая функция и ее производная для x2 (которая по сути 0)
double g1_x2(double x) { return asin((x * x) / 5); }
double g1_x2_derivative(double x) {
    return fabs((2 * x) / sqrt(25 - pow(x, 4)));
}

void main1() {
    printf("Первое уравнение.\n\n");

    double e = 0;
    printf("Введите точность e: ");
    scanf("%lf", &e);
    while (getchar() != '\n')
        ;
    printf("\n");

    // Первый x (который между 2 и 2.1)
    printf("Вычисление x1:\n");
    double x = 1.57; // pi / 2
    double x_last = g1_x1(x);
    printf("Первое приближение: %lf\n", x);
    if (g1_x1_derivative(x) >= 1) {
        printf("Не сходится.........\n");
        return;
    }

    while (fabs(x - x_last) >= e) {
        x_last = x;
        x = g1_x1(x_last);
        printf("x[n], x[n + 1] = %lf, %lf\n", x_last, x);
    }

    printf("x1: %lf\n", x);

    // Второй x (который 0)
    printf("Вычисление x2:\n");
    x = 1;
    x_last = g1_x2(x);
    printf("Первое приближение: %lf\n", x);
    if (g1_x2_derivative(x) >= 1) {
        printf("Не сходится.........\n");
        return;
    }

    while (fabs(x - x_last) >= e) {
        x_last = x;
        x = g1_x2(x_last);
        printf("x[n], x[n + 1] = %lf, %lf\n", x_last, x);
    }

    printf("x2: %lf\n", x);
}

// Второе уравнение
// Выходная функция и ее производная для x1
double g2_x1(double x) { return sin(x) + 0.15; }
double g2_x1_derivative(double x) { return fabs(cos(x)); }

void main2() {
    printf("Второе уравнение.\n\n");

    double e = 0;
    printf("Введите точность e: ");
    scanf("%lf", &e);
    while (getchar() != '\n')
        ;
    printf("\n");

    printf("Вычисление x1:\n");
    double x = 1.57; // pi / 2
    double x_last = g2_x1(x);
    printf("Первое приближение: %lf\n", x);
    if (g2_x1_derivative(x) >= 1) {
        printf("Не сходится.........\n");
        return;
    }

    while (fabs(x - x_last) >= e) {
        x_last = x;
        x = g2_x1(x_last);
        printf("x[n], x[n + 1] = %lf, %lf\n", x_last, x);
    }

    printf("x1: %lf\n", x);
}

// Третье уравнение
// Выходная первая функция и ее производная для x1 (которая между 2 и 2.5)
double g3_x1(double x) { return sqrt(sqrt(9 + x) - x + 4); }
double g3_x1_derivative(double x) {
    return fabs((1 / (2 * sqrt(9 + x)) - 1) / (2 * sqrt(sqrt(9 + x) - x + 4)));
}
// Выходная вторая функция и ее производная для x2 (которая между -3.5 и -2.5)
double g3_x2(double x) { return -sqrt(sqrt(9 + x) - x + 4); }
double g3_x2_derivative(double x) {
    return fabs((1 / (2 * sqrt(9 + x)) - 1) / (2 * sqrt(sqrt(9 + x) - x + 4)));
}

void main3() {
    printf("Третье уравнение.\n\n");
    double e = 0;
    printf("Введите точность e: ");
    scanf("%lf", &e);
    while (getchar() != '\n')
        ;
    printf("\n");

    // Первый x (положительный)
    printf("Вычисление x1:\n");
    double x = 1.57; // прикол))
    double x_last = g3_x1(x);
    printf("Первое приближение: %lf\n", x);
    if (g3_x1_derivative(x) >= 1) {
        printf("Не сходится.........\n");
        return;
    }

    while (fabs(x - x_last) >= e) {
        x_last = x;
        x = g3_x1(x_last);
        printf("x[n], x[n + 1] = %lf, %lf\n", x_last, x);
    }

    printf("x1: %lf\n", x);

    // Второй x (отрицательный)
    printf("\nВычисление x2:\n");
    x = -1.57; // прикол))
    x_last = g3_x2(x);
    printf("Первое приближение: %lf\n", x);
    if (g3_x2_derivative(x) >= 1) {
        printf("Не сходится.........\n");
        return;
    }

    while (fabs(x - x_last) >= e) {
        x_last = x;
        x = g3_x2(x_last);
        printf("x[n], x[n + 1] = %lf, %lf\n", x_last, x);
    }

    printf("x2: %lf\n", x);
}

int run() {
    int equation = 0;
    printf("Уравнения:\n");
    printf("(1) x^2 - 5sin(x) = 0\n");
    printf("(2) sin(x) - x + 0.15 = 0\n");
    printf("(3) x - (9 + x)^(1/2) + x^2 - 4 = 0\n");
    printf("Напишите номер уравнения: ");
    scanf("%d", &equation);
    while (getchar() != '\n')
        ;

    printf("\n\n\n");
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
    default:
        printf("Ошибка! Введен неверный пример.\n");
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
