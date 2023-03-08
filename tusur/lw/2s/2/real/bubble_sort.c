int sort(int *arr, int n) {
    int comparison_rearrangment_count = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (arr[j] < arr[j - 1]) {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;

                comparison_rearrangment_count++;
            }
            comparison_rearrangment_count++;
        }
    }

    return comparison_rearrangment_count;
}
