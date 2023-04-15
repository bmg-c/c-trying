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

// void merge(int *arr, int first, int mid, int last) {
//     int i = 0, j = 0;
//     int *arr_result = (int *)malloc((last - first) * sizeof(int));
//
//     while (first + i < mid && mid + j < last) {
//         if (arr[first + i] < arr[mid + j]) {
//             arr_result[i + j] = arr[first + i];
//             i++;
//         } else {
//             arr_result[i + j] = arr[mid + j];
//             j++;
//         }
//     }
//
//     while (first + i < mid) {
//         arr_result[i + j] = arr[first + i];
//         i++;
//     }
//
//     while (first + j < last) {
//         arr_result[i + j] = arr[mid + j];
//         j++;
//     }
//
//     for (int i = 0; i < i + j; i++) {
//         arr[first + i] = arr_result[i];
//     }
// }

void merge(int *arr, int first, int mid, int last) {
    int *arr_result = (int *)malloc((last - first) * sizeof(int));
    int i = first, j = mid, k = 0;

    while (i < mid && j <= last) {
        if (arr[i] > arr[j]) {
            arr_result[k] = arr[j];
            j++, k++;
        } else if (arr[j] > arr[i]) {
            arr_result[j] = arr[i];
            i++, k++;
        } else {
            arr_result[k] = arr[i];
            arr_result[k + 1] = arr[j];
            k += 2, i++, j++;
        }
    }
    if (i < mid)
        for (; i <= mid - 1; i++)
            arr_result[i + k] = arr[i];

    if (j <= last)
        for (; j <= last; j++)
            arr_result[j + k] = arr[j];

    for (int ind = 0; ind <= last - first; ind++)
        arr[first + ind] = arr_result[i];

    free(arr_result);
}

void merge_sort_recursive(int *arr, int first, int last) {
    if (last <= first)
        return;
    int mid = (first + last) / 2;
    merge_sort_recursive(arr, first, mid);
    merge_sort_recursive(arr, mid + 1, last);
    merge(arr, first, mid + 1, last);
}

int sort(int *arr, int size) {
    int comp_swap_amount = 0;

    merge_sort_recursive(arr, 0, size - 1);

    // for (int i = 1; i < size; i *= 2)
    //     for (int j = 0; j < size - i; j += 2 * i) {
    //         int min = j + 2 * i;
    //         if (min > size)
    //             min = size;
    //         merge(arr, j, j + i, min);
    //     }

    return comp_swap_amount;
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
    print_arr(arr, elements_amount);
    printf("\n");

    int comp_swap_count = sort(arr, elements_amount);
    printf("\n");
    print_arr(arr, elements_amount);
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
