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

int sort(int *arr, int elements_amount) {
    int comp_swap_count = 0;
    int step = elements_amount - 1;

    while (step > 0) {
        int flag = 1;
        while (flag == 1) {
            flag = 0;

            int i, j;
            for (i = 0, j = step; j < elements_amount;
                 i++, j++, comp_swap_count++) {
                if (arr[i] > arr[j]) {
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;

                    comp_swap_count++;
                    flag = 1;
                }
            }
        }

        step = (step * 8) / 11;
    }

    return comp_swap_count;
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
    printf("\n");

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
