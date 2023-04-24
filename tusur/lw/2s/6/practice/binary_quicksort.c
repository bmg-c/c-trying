#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define True 1
#define False 0
#define ARRAY_SIZE_STEP 1
#define TESTS_AMOUNT 100
#define MAX_ARRAY_SIZE 1000

void print_arr(char *arr, int size) {
    for (int i = 0; i < size; i++)
        printf("%4d ", arr[i]);
    printf("\n");
}

char *create_rand_arr(int size) {
    char *arr = (char *)malloc(sizeof(char) * size);
    for (int i = 0; i < size; i++)
        arr[i] = 97 + rand() % 26;

    return arr;
}

int get_digit(char ch, int digit) {
    return (ch >> (sizeof(ch) * 8 - digit)) & 1;
}

void print_table(char *arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int digit = 1; digit <= sizeof(char) * 8; digit++)
            printf("%d", get_digit(arr[i], digit));
        printf("\n");
    }
    printf("\n");
}

void binary_quicksort(char *arr, int start, int end, int digit, int size) {
    int first = start;
    int last = end;
    int is_changed = 0;

    printf("start, end: %d, %d. digit(%d)\n", start, end, digit);
    while (1) {
        while (get_digit(arr[start], digit) != 1 && start != end)
            start++;
        if (start == end)
            break;

        printf("\tstart, end: %d, %d. digit(%d)\n", start, end, digit);

        while (get_digit(arr[end], digit) != 0 && start != end)
            end--;
        if (start == end)
            break;

        printf("\tstart, end: %d, %d. digit(%d)\n", start, end, digit);

        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        is_changed = 1;
    }

    start--;
    end--;

    printf("start, end: %d, %d. digit(%d)\n", start, end, digit);
    print_table(arr, size);

    if (digit == sizeof(char) * 8)
        return;

    if (is_changed == 0) {
        binary_quicksort(arr, first, last, digit + 1, size);
        return;
    }

    if (first < end) {
        // printf("Первый подмассив\n");
        binary_quicksort(arr, first, end, digit + 1, size);
    }
    if (end + 1 < last) {
        // printf("Второй подмассив\n");
        binary_quicksort(arr, end + 1, last, digit + 1, size);
    }
}


void sort(char *arr, int size) { binary_quicksort(arr, 0, size - 1, 1, size); }

int is_arr_sorted(char *arr, int size) { // 1 - True
    for (int i = 1; i < size; i++)
        if (arr[i] < arr[i - 1])
            return False;
    return True;
}

int test_sort() {
    for (int size = ARRAY_SIZE_STEP; size <= MAX_ARRAY_SIZE;
         size += ARRAY_SIZE_STEP) {
        for (int test = 1; test <= TESTS_AMOUNT; test++) {
            char *arr = create_rand_arr(size);
            sort(arr, size);
            if (is_arr_sorted(arr, size) == False)
                return False;
            free(arr);
        }
    }

    return True;
}

int run() {
    int size = 0;
    printf("Введите количество элементов в массиве: ");
    scanf("%d", &size);
    printf("\n");

    char *arr = create_rand_arr(size);
    print_arr(arr, size);
    printf("\n");

    // int comp_swap_count = sort(arr, size);
    sort(arr, size);
    printf("\n");
    print_arr(arr, size);
    // printf("Количество сравнений и перестановок: %d", comp_swap_count);

    printf("\n");
    if (is_arr_sorted(arr, size) == True)
        printf("Сортировка прошла успешно\n");
    else
        printf("Сортировка не удалась\n");

    // if (test_sort() == True)
    //     printf("Тест сортировки прошел успешно\n");
    // else
    //     printf("Тест сортировки не удался\n");

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
