#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 0;
    scanf("%d", &n);

    float c = 0;
    scanf("%f", &c);

    float* arr = (float*) malloc(sizeof(float) * n);
    for (int i = 0; i < n; i++)
        scanf("%f", &arr[i]);

    int smaller_amount = 0; // Эл-ов меньше чем C
    int last_negative_index = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] < c)
            smaller_amount++;

        if (arr[i] < 0)
            last_negative_index = i;
    }
    printf("%d\n", smaller_amount);

    int sum = 0; // Сумма после последнего отриц. эл-та
    if (last_negative_index >= 0)
        for (int i = last_negative_index; i < n; i++)
            sum += (int) arr[i]; // Отделяем плавающую точку преобразованием
                                 // типов.
    printf("%d\n", sum);

    for (int i = 0; i < n; i++) {
        float remainder = arr[i] - ((int) arr[i]);
        // Для отриц. эл-ов
        if (arr[i] < 0)
            remainder += 1;

        printf("%.4f ", remainder);
    }

    free(arr);

    return 0;
}
