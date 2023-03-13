#include <math.h>
#include <stdio.h>
#include <stdlib.h>

char **generate_gray(int n) {
    int combinations_amount = pow(2, n) - 1;
    char **gray_code = (char **)malloc(sizeof(char *) * combinations_amount);
    for (int i = 0; i < combinations_amount; i++) {
        gray_code[i] = (char *)malloc(sizeof(char) * n);
        for (int j = 0; j < n; j++)
            gray_code[i][j] = '0';
    }

    for (int i = 0; i < n; i++) {
        
    }

    return gray_code;
}

int run() {
    int n, k;
    printf("Введите мощность множества и выборку (n k): ");
    scanf("%d %d", &n, &k);

    char **gray_code = generate_gray(n);
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
