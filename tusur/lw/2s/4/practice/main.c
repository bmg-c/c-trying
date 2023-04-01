#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILENAME_LENGTH 256
#define TESTS_AMOUNT 5
#define MAX_ELEMENETS_AMOUNT 10000

int *create_rand_arr(int elements_amount) {
    int *arr = (int *)malloc(sizeof(int) * elements_amount);
    for (int i = 0; i < elements_amount; i++)
        arr[i] = rand() % 101;

    return arr;
}

int sort(int *arr, int elements_amount) {
    int comp_swap_count = 0;

    int min_ind = 0;
    for (int i = 1; i < elements_amount; i++) {
        if (arr[i] < arr[min_ind])
            min_ind = i;
        comp_swap_count++;
    }

    int temp = arr[min_ind];
    arr[min_ind] = arr[0];
    arr[0] = temp;

    comp_swap_count++;

    for (int i = 2; i < elements_amount; i++) {
        int value = arr[i];
        int j;
        for (j = i - 1;; j--) {
            if (arr[j] > value) {
                arr[j + 1] = arr[j];

                comp_swap_count++;
            } else {
                comp_swap_count++;

                break;
            }

            comp_swap_count++;
        }
        arr[j + 1] = value;
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
