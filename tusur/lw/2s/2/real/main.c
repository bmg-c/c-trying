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
    int comparison_rearrangment_count = 0;
    for (int i = elements_amount; i > 1; i--) {
        int max_ind = 0;
        for (int j = 1; j < i; j++) {
            if (arr[max_ind] < arr[j])
                max_ind = j;
            comparison_rearrangment_count++;
        }

        int temp = arr[max_ind];
        arr[max_ind] = arr[i - 1];
        arr[i - 1] = temp;

        comparison_rearrangment_count++;
    }

    return comparison_rearrangment_count;
}

void run_tests(char *file_name) {
    FILE *csv_file = fopen(file_name, "w");

    for (int elements_amount = 100; elements_amount <= MAX_ELEMENETS_AMOUNT;
         elements_amount += 100) {
        int average_comparison_rearrangment = 0;
        for (int test = 1; test <= TESTS_AMOUNT; test++) {
            int *arr = create_rand_arr(elements_amount);
            average_comparison_rearrangment +=
                sort(arr, elements_amount) / TESTS_AMOUNT;
            free(arr);
        }
        fprintf(csv_file, "%d; %d\n", elements_amount,
                average_comparison_rearrangment);
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
