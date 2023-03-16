/* Домашняя работа n2, Вариант 7. Сочетания код Грея.
 * Лифанов Иван Сергеевич 422-3. */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

char **generate_string_matrix(int n) {
    int combinations_amount = pow(2, n);
    char **gray_code = (char **)malloc(sizeof(char *) * combinations_amount);
    for (int i = 0; i < combinations_amount; i++) {
        gray_code[i] = (char *)malloc(sizeof(char) * (n + 1));
        int j;
        for (j = 0; j < n; j++)
            gray_code[i][j] = '0';
        gray_code[i][j] = '\0';
    }

    return gray_code;
}

char **generate_gray(int n) {
    int combinations_amount = pow(2, n);
    char **gray_code = generate_string_matrix(n);

    /* Алгоритм заполняет каждый символ построчно символами j..j+2^i нулями
     * затем однерками, затем однерками, затем нулями и повторяя, пока
     * j < combinations_amount */
    int j = 0; // Счет текущей строки
    int elem; // Счет шага заполнения
    for (int i = 0; i < n;) {
        if ((elem = j + pow(2, i)) > combinations_amount) {
            i++;
            j = 0;
            continue;
        }
        for (; j < elem; j++)
            gray_code[j][n - i - 1] = '0';

        if ((elem = j + pow(2, i)) > combinations_amount) {
            i++;
            j = 0;
            continue;
        }
        for (; j < elem; j++)
            gray_code[j][n - i - 1] = '1';

        if ((elem = j + pow(2, i)) > combinations_amount) {
            i++;
            j = 0;
            continue;
        }
        for (; j < elem; j++)
            gray_code[j][n - i - 1] = '1';

        if ((elem = j + pow(2, i)) > combinations_amount) {
            i++;
            j = 0;
            continue;
        }
        for (; j < elem; j++)
            gray_code[j][n - i - 1] = '0';
    }

    return gray_code;
}

void print_gray(char **gray, int n) {
    int combinations_amount = pow(2, n);
    printf("Код Грея:\n");
    for (int i = 0; i < combinations_amount; i++)
        printf("\t%s\n", gray[i]);
    printf("\n");
}

void print_gray_sorted(char **gray, int n, int k) {
    int combinations_amount = pow(2, n);
    printf("Код Грея Соритрованный (%d единиц):\n", k);
    for (int i = 0; i < combinations_amount; i++) {
        int one_amount = 0;
        for (int j = 0; j < n; j++)
            if (gray[i][j] == '1')
                one_amount++;
        if (one_amount == k)
            printf("\t%s\n", gray[i]);
    }
    printf("\n");
}

int run() {
    int n, k;
    printf("Введите мощность множества и выборку (n k): ");
    scanf("%d %d", &n, &k);

    char **gray_code = generate_gray(n);
    print_gray(gray_code, n);

    print_gray_sorted(gray_code, n, k);

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
