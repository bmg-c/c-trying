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

int binarySearch(int a[], int item, int low, int high) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (item == a[mid])
            return mid + 1;
        else if (item > a[mid])
            low = mid + 1;
        else
            high = mid - 1;
    }

    return low;
}

// Function to sort an array a[] of size 'n'
void sort(int a[], int n) {
    int i, loc, j, k, selected;

    for (i = 1; i < n; ++i) {
        j = i - 1;
        selected = a[i];

        // find location where selected should be inserted
        loc = binarySearch(a, selected, 0, j);

        // Move all elements after location to create space
        while (j >= loc) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = selected;
    }
}

int run() {
    int elements_amount = 0;
    printf("Введите количество элементов в массиве: ");
    scanf("%d", &elements_amount);
    printf("\n");

    int *arr = create_rand_arr(elements_amount);
    print_arr(arr, elements_amount);
    printf("\n");

    sort(arr, elements_amount);
    printf("\n");
    print_arr(arr, elements_amount);
    // printf("Количество сравнений и перестановок: %d", comp_swap_count);

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
