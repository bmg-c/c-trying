#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define START_CHAR 48
#define R 10
#define ARR_SIZE_STEP 5
#define MAX_ARR_SIZE 100
#define STR_SYMBOL_STEP 1
#define MAX_SYMBOL_AMOUNT 9
#define TESTS_AMOUNT 1000

void print_arr_str_arr(char ***arr, int arr_size) {
    for (int j = 0; j < R; j++) {
        for (int i = 0; i < arr_size; i++)
            printf("%s ", arr[j][i]);
        printf("\n");
    }
}

void print_str_arr(char **arr, int arr_size) {
    for (int i = 0; i < arr_size; i++)
        printf("%s ", arr[i]);
    printf("\n");
}

void print_arr(int *arr, int arr_size) {
    for (int i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

char **create_rand_arr(int arr_size, int str_size) {
    char **arr = (char **)malloc(sizeof(char *) * arr_size);
    for (int i = 0; i < arr_size; i++)
        arr[i] = (char *)malloc(sizeof(char) * (str_size + 1));

    for (int i = 0; i < arr_size; i++) {
        for (int j = 0; j < str_size; j++)
            arr[i][j] = START_CHAR + rand() % R;
        arr[i][str_size] = '\0';
    }

    return arr;
}

int get_digit(char *str, int digit) { return str[digit] - START_CHAR; }

void _sort(char **arr, int start, int end, int digit) {
    if (arr[0][digit] == '\0' || start >= end)
        return;

    int *count_arr = (int *)malloc(sizeof(int) * (R + 1));
    for (int i = 0; i < R; i++)
        count_arr[i] = 0;

    for (int i = start; i <= end; i++)
        count_arr[get_digit(arr[i], digit)]++;

    char **temp_arr = (char **)malloc(sizeof(char *) * (end - start + 1));
    for (int i = start; i <= end; i++)
        temp_arr[i - start] = arr[i];

    for (int num = 0, i = start; num < R && i <= end; num++) {
        int temp_step = 0;
        for (int k = count_arr[num]; k >= 0; k--)
            for (; temp_step <= end - start; temp_step++) // j < amount
                if (get_digit(temp_arr[temp_step], digit) == num) {
                    arr[i] = temp_arr[temp_step];
                    i++;
                }
    }

    free(temp_arr);

    for (int i = 1; i < R; i++)
        count_arr[i] += count_arr[i - 1];
    for (int i = R; i >= 0; i--)
        count_arr[i] = count_arr[i - 1];
    count_arr[0] = 0;
    count_arr[R] = end - start + 1;

    for (int i = 0; i < R; i++)
        _sort(arr, start + count_arr[i], start + count_arr[i + 1] - 1,
              digit + 1);

    free(count_arr);
}

void sort(char **arr, int arr_size) { _sort(arr, 0, arr_size - 1, 0); }

int run() {
    int arr_size = 0, str_size = 0;
    printf(
        "Введите количество строк и символов в строке (arr_size str_size): ");
    scanf("%d %d", &arr_size, &str_size);
    printf("\n");

    char **arr = create_rand_arr(arr_size, str_size);
    print_str_arr(arr, arr_size);
    printf("\n");

    sort(arr, arr_size);
    printf("\n");
    print_str_arr(arr, arr_size);
    int is_wrong = 0;
    for (int i = 1; i < arr_size; i++)
        if (atoi(arr[i - 1]) > atoi(arr[i])) {
            printf("%d > %d. Ошибочка\n", atoi(arr[i - 1]), atoi(arr[i]));
            is_wrong = 1;
        } else {
            printf("%d <= %d\n", atoi(arr[i - 1]), atoi(arr[i]));
        }
    for (int i = 0; i < arr_size; i++)
        free(arr[i]);
    free(arr);

    // int is_wrong = 0;
    // for (int arr_size = ARR_SIZE_STEP; arr_size <= MAX_ARR_SIZE;
    //      arr_size += ARR_SIZE_STEP) {
    //     for (int str_size = STR_SYMBOL_STEP; str_size <= MAX_SYMBOL_AMOUNT;
    //          str_size += STR_SYMBOL_STEP)
    //         for (int test = 1; test <= TESTS_AMOUNT; test++) {
    //             char **arr = create_rand_arr(arr_size, str_size);
    //             print_str_arr(arr, arr_size);
    //             sort(arr, arr_size);
    //
    //             print_str_arr(arr, arr_size);
    //             for (int i = 1; i < arr_size; i++) {
    //                 if (atoi(arr[i - 1]) > atoi(arr[i])) {
    //                     // printf("%d > %d. Ошибочка\n", atoi(arr[i - 1]),
    //                     //        atoi(arr[i]));
    //                     is_wrong = 1;
    //                 } else {
    //                     // printf("%d <= %d\n", atoi(arr[i - 1]), atoi(arr[i]));
    //                 }
    //             }
    //             printf("\n");
    //
    //             for (int i = 0; i < arr_size; i++)
    //                 free(arr[i]);
    //             free(arr);
    //         }
    // }

    // if (is_wrong == 1)
    //     printf("Во время тестирования произошла ошибка\n");
    // else
    //     printf("При тестировании не было найдено ошибок\n");

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
#ifdef _WIN32
    system("chcp 65001");
#endif

    srand(time(NULL));

    if (run() == EXIT_FAILURE)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
