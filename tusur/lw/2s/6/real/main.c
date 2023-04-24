#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILENAME_LENGTH 256
#define TESTS_AMOUNT 30
#define MAX_ELEMENETS_AMOUNT 10000

int *create_rand_arr(int elements_amount) {
    int *arr = (int *)malloc(sizeof(int) * elements_amount);
    for (int i = 0; i < elements_amount; i++)
        arr[i] = rand() % 101;

    return arr;
}

int merge(int *arr, int first, int mid, int last) {
    int comp_swap_amount = 0;

    int *arr_result = (int *)malloc(sizeof(int) * (last - first + 1));
    int i = first, j = mid, k = 0;

    while (i < mid && j <= last) {
        if (arr[i] > arr[j]) {
            arr_result[k] = arr[j];
            j++, k++;
            comp_swap_amount += 2;
        } else if (arr[i] < arr[j]) {
            arr_result[k] = arr[i];
            i++, k++;
            comp_swap_amount += 2;
        } else {
            arr_result[k] = arr[i];
            arr_result[k + 1] = arr[j];
            i++, j++, k += 2;
            comp_swap_amount += 3;
        }
    }

    for (; i < mid; i++, k++) {
        arr_result[k] = arr[i];
        comp_swap_amount++;
    }
    for (; j <= last; j++, k++) {
        arr_result[k] = arr[j];
        comp_swap_amount++;
    }

    for (k = 0; k <= (last - first); k++) {
        arr[k + first] = arr_result[k];
        comp_swap_amount++;
    }

    free(arr_result);
    return comp_swap_amount;
}

int sort(int *arr, int size) {
    int comp_swap_amount = 0;

    for (int h = 1; h <= size; h *= 2)
        for (int i = 0; i <= size - h; i += 2 * h) {
            int last = i + 2 * h - 1;
            if (last >= size)
                last = size - 1;
            comp_swap_amount += merge(arr, i, i + h, last);
        }

    return comp_swap_amount;
}

void run_tests(char *file_name) {
    FILE *csv_file = fopen(file_name, "w");

    for (int elements_amount = 100; elements_amount <= MAX_ELEMENETS_AMOUNT;
         elements_amount += 100) {
        int average_comparison_swap = 0;
        for (int test = 1; test <= TESTS_AMOUNT; test++) {
            int *arr = create_rand_arr(elements_amount);
            average_comparison_swap +=
                sort(arr, elements_amount) / TESTS_AMOUNT;
            free(arr);
        }
        fprintf(csv_file, "%d; %d\n", elements_amount,
                average_comparison_swap);
    }

    fclose(csv_file);
}
int run() {
    char file_name[MAX_FILENAME_LENGTH];
    printf("Введите полное название файла, куда будут записываться данные: ");
    scanf("%255s", file_name); // \0 в конце
    printf("\n%d\n", EXIT_SUCCESS);

    run_tests(file_name);
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
