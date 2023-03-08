#include <stddef.h>
#include <stdio.h>

int maxSequence(const int* array, size_t n) {
    if (n == 0)
        return 0;

    int sum = 0;
    int neg_num_count = 0;
    for (int i = 0; i < n; i++) {
        int temp_sum = 0;
        if (array[i] < 0)
            neg_num_count += 1;
        for (int j = 0; j < n - i; j++) {
            temp_sum += array[i + j];
            if (temp_sum > sum)
                sum = temp_sum;
        }
    }
    if (neg_num_count == n)
        return 0;

    return sum;
}

int main() {
    printf("%d", maxSequence(arr, 49984));
}