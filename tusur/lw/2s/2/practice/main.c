#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILENAME_LENGTH 256
#define TESTS_AMOUNT 5
#define MAX_ELEMENETS_AMOUNT 10000

int bubble_sort(int *arr, int n) {
    int comparisons_rearrangment_count = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (arr[j] < arr[j - 1]) {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;

                comparisons_rearrangment_count++;
            }
            comparisons_rearrangment_count++;
        }
    }

    return comparisons_rearrangment_count;
}

int *create_rand_arr(int elements_amount) {
    int *arr = (int *)malloc(sizeof(int) * elements_amount);
    for (int i = 0; i < elements_amount; i++)
        arr[i] = rand() % 101;

    return arr;
}

void run_tests(char *file_name) {
    FILE *csv_file = fopen(file_name, "w");

    for (int elements_amount = 100; elements_amount <= MAX_ELEMENETS_AMOUNT;
         elements_amount += 100) {
        int average_comparisons_rearrangment = 0;
        for (int test = 1; test <= TESTS_AMOUNT; test++) {
            int *arr = create_rand_arr(elements_amount);
            average_comparisons_rearrangment +=
                bubble_sort(arr, elements_amount) / TESTS_AMOUNT;
            free(arr);
        }
        fprintf(csv_file, "%d; %d\n", elements_amount,
                average_comparisons_rearrangment);
    }

    fclose(csv_file);
}
int run() {
    char file_name[MAX_FILENAME_LENGTH];
    printf("Введите полное название файла, куда будут записываться данные: ");
    scanf("%255s", file_name); // \0 в конце
    printf("\n");

    // int n = 2;
    // int *arr = (int *)malloc(sizeof(int) * n);
    // arr[0] = 4;
    // arr[1] = 1;
    // int comparisons_rearrangment_count = bubble_sort(arr, n);
    //
    // free(arr);

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
