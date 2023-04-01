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

    print_arr(arr, elements_amount);
    comp_swap_count++;

    for (int i = 2; i < elements_amount; i++) {
        int value = arr[i];
        int j;
        for (j = i - 1;; j--) {
            if (arr[j] > value) {
                arr[j + 1] = arr[j];

                print_arr(arr, elements_amount);
                comp_swap_count++;
            } else {
                print_arr(arr, elements_amount);
                comp_swap_count++;

                break;
            }

            comp_swap_count++;
        }
        arr[j + 1] = value;
    }

    return comp_swap_count;
}

int run() {
    int elements_amount = 0;
    printf("Введите количество элементов в массиве: ");
    scanf("%d", &elements_amount);
    printf("\n");

    int *arr = create_rand_arr(elements_amount);
    print_arr(arr, elements_amount);
    printf("\n");

    int comp_swap_count = sort(arr, elements_amount);
    printf("\n");
    print_arr(arr, elements_amount);
    printf("Количество сравнений и перестановок: %d", comp_swap_count);

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
