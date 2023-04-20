#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define True 1
#define False 0

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

int is_arr_sorted(int *arr, int elements_amount) { // 1 - True
    for (int i = 1; i < elements_amount; i++)
        if (arr[i] < arr[i - 1])
            return False;
    return True;
}

int run() {
    int elements_amount = 0;
    printf("Введите количество элементов в массиве: ");
    scanf("%d", &elements_amount);
    printf("\n");

    int *arr = create_rand_arr(elements_amount);
    // print_arr(arr, elements_amount);
    printf("\n");

    int comp_swap_count = sort(arr, elements_amount);
    // printf("\n");
    // print_arr(arr, elements_amount);
    printf("Количество сравнений и перестановок: %d", comp_swap_count);

    printf("\n");
    if (is_arr_sorted(arr, elements_amount) == True)
        printf("Сортировка прошла успешно\n");
    else
        printf("Сортировка не удалась\n");

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
