#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define True 1
#define False 0

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

int is_arr_sorted(int *arr, int size) { // 1 - True
    for (int i = 1; i < size; i++)
        if (arr[i] < arr[i - 1])
            return False;
    return True;
}

void print_arr(int *arr, int size) {
    for (int i = 0; i < size; i++)
        printf("%4d ", arr[i]);
    printf("\n");
}

int *create_rand_arr(int size) {
    int *arr = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
        arr[i] = rand() % 101;

    return arr;
}

int run() {
    int size = 0;
    printf("Введите количество элементов в массиве: ");
    scanf("%d", &size);
    printf("\n");

    int *arr = create_rand_arr(size);
    print_arr(arr, size);
    printf("\n");

    int comp_swap_count = sort(arr, size);
    printf("\n");
    print_arr(arr, size);
    printf("Количество сравнений и перестановок: %d", comp_swap_count);

    printf("\n");
    if (is_arr_sorted(arr, size) == True)
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
