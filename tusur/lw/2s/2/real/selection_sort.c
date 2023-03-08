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

        printf("%d %d %d: ", comparison_rearrangment_count, i, max_ind + 1);
        print_arr(arr, elements_amount);

        comparison_rearrangment_count++;
    }

    return comparison_rearrangment_count;
}

int run() {
    int elements_amount = 0;
    printf("Введите количество элементов в массиве: ");
    scanf("%d", &elements_amount);
    printf("\n");

    int *arr = create_rand_arr(elements_amount);
    print_arr(arr, elements_amount);
    printf("\n");

    int comparison_rearrangment_count = sort(arr, elements_amount);
    printf("\n");
    print_arr(arr, elements_amount);
    printf("Количество сравнений и перестановок: %d",
           comparison_rearrangment_count);

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
