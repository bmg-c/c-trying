#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_arr(int *arr, int elements_amount) {
    for (int i = 0; i < elements_amount; i++)
        printf("%4d ", arr[i]);
    printf("\n");
}

int *create_rand_arr(int elements_amount) {
    int *arr = (int *)malloc(sizeof(int) * elements_amount);
    for (int i = 0; i < elements_amount; i++)
        arr[i] = rand() % 101;

    return arr;
}

int sort(int *arr, int elements_amount) {
    int comparison_swap_count = 0;

    int start = 0;
    int end = elements_amount - 1;
    int swapped = 1;

    while (swapped == 1) {
        swapped = 0;
        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;

                swapped = 1;
                comparison_swap_count++;
            }
            comparison_swap_count++;
        }
        end--;

        if (swapped == 0)
            break;

        print_arr(arr, elements_amount);

        swapped = 0;
        for (int i = end - 1; i >= start; i--) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;

                swapped = 1;
                comparison_swap_count++;
            }
            comparison_swap_count++;
        }
        start++;

        print_arr(arr, elements_amount);
        printf("\n");
    }

    return comparison_swap_count;
}

int run() {
    int elements_amount = 0;
    printf("Введите количество элементов в массиве: ");
    scanf("%d", &elements_amount);
    printf("\n");

    int *arr = create_rand_arr(elements_amount);
    print_arr(arr, elements_amount);
    printf("\n");

    int comparison_swap_count = sort(arr, elements_amount);
    printf("\n");
    print_arr(arr, elements_amount);
    printf("Количество сравнений и перестановок: %d",
           comparison_swap_count);

    free(arr);
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
