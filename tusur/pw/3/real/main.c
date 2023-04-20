#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float recursive(int k) {
    if (k != 0)
        return k * recursive(k - 1) + 1.0 / ((float)k);
    return 1;
}

int run() {
    int k = 0;
    printf("Введите значение k (k): ");
    scanf("%d", &k);
    printf("\n");

    printf("Значение a(k): %f\n", recursive(k));

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
