#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int n = 0;
    scanf("%d", &n); // n

    float* arr = (float*) malloc(sizeof(float) * n);
    for (int i = 0; i < n; i++)
        scanf("%f", &arr[i]);

    // for (int i = 0; i < n; i++)
    //     printf("%f ", arr[i]);

    float min = fabs(arr[0]);
    for (int i = 1; i < n; i++)
        if (min > fabs(arr[i]))
            min = fabs(arr[i]);
    printf("%.4f\n", min);

    float sum = 0;    
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            for (int j = i + 1; j < n; j++) {
                sum += fabs(arr[j]);
            }
            break;
        }
    }
    printf("%.4f\n", sum);

    for (int i = 1; i < n; i += 2)
        printf("%.4f ", arr[i]);

    for (int i = 0; i < n; i += 2)
        printf("%.4f ", arr[i]);

    return 0;
}
