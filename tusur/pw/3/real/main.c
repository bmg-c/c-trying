#include <stdio.h>
#include <stdlib.h>

float recursive(int k) {
    if (k != 0)
        return k * recursive(k - 1) + 1.0 / k;

    return 1;
}

float iterational(int k) {
    float sum = 1;

    for (int i = 1; i <= k; i++)
        sum = i * sum + 1.0 / i;

    return sum;
}

int run() {
    int k = 0;
    printf("Введите значение k (k): ");
    scanf("%d", &k);
    printf("\n");

    printf("Значение рекурсивной a(k): %f\n", recursive(k));
    printf("Значение не рекурсивной a(k): %f\n", iterational(k));

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
