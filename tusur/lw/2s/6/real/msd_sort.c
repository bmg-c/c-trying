#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define START_CHAR 48
#define R 10

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

    int *count_arr = (int *)malloc(sizeof(int) * R);
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

    // print_arr(count_arr, R);
    // print_str_arr(arr, 10);
    free(count_arr);
    free(temp_arr);

    // for (int i = start + 1; i <= end; i++) {
    //     int j;
    //     char *elem = arr[i];
    //
    //     for (j = i - 1; j >= start && get_digit(arr[j], digit) > get_digit(elem, digit);
    //          j--)
    //         arr[j + 1] = arr[j];
    //     arr[j + 1] = elem;
    // }

    int *split_points = (int *)malloc(sizeof(int) * (R + 1));
    for (int i = 0; i < R; i++)
        split_points[i] = 0;
    split_points[R] = end + 1;

    int num = 0;
    int i = start;
    while (i <= end && num < R) {
        split_points[num] = i;

        while (get_digit(arr[i], digit) == num && i < end && num < R)
            i++;

        num++;
    }
    // print_arr(split_points, R + 1);

    for (int i = 0; i < R; i++)
        _sort(arr, split_points[i], split_points[i + 1] - 1, digit + 1);

    free(split_points);
}

void sort(char **arr, int arr_size) { _sort(arr, 0, arr_size - 1, 0); }

int run() {
    // int arr_size = 0, str_size = 0;
    // printf(
    //     "Введите количество строк и символов в строке (arr_size str_size): ");
    // scanf("%d %d", &arr_size, &str_size);
    // printf("\n");
    //
    // char **arr = create_rand_arr(arr_size, str_size);
    // print_str_arr(arr, arr_size);
    // printf("\n");
    //
    // sort(arr, arr_size);
    // printf("\n");
    // print_str_arr(arr, arr_size);
    for (int arr_size = 10, str_size = 3, test = 1; test <= 100; test++) {
        char **arr = create_rand_arr(arr_size, str_size);
        print_str_arr(arr, arr_size);
        sort(arr, arr_size);

        print_str_arr(arr, arr_size);
        for (int i = 1; i < arr_size; i++) {
            printf("%d\n", atoi(arr[i]));
            if (atoi(arr[i - 1]) > atoi(arr[i]))
                printf("Ошиб очка\n");
        }
        printf("\n");

        for (int i = 0; i < arr_size; i++)
            free(arr[i]);
        free(arr);
    }

    // for (int i = 0; i < arr_size; i++)
    //     free(arr[i]);
    // free(arr);
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
