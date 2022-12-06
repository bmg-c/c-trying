/*
** Вариант 7.
В одномерном массиве, состоящем изn целых элементов, вычислить:
А) сумму отрицательных элементов.
Б) количество элементов массива, расположенных между первым и последним
   четными положительными элементами.
В) удалить из массива все минимальные элементы, дополнительный массив
   не использовать.
*/
#include "stdio.h"
#include "stdlib.h"


int main() {
    int n, i;
    printf("Введите размерность массива: ");
    while (1) {
        scanf("%d", &n);
        if (getchar() != '\n') {
            printf("Данные некорректны.\nВведите их снова: ");
            while (getchar() != '\n');
            continue;
        }
        if (n < 1) {
            printf("Данные некорректны.\nВведите их снова: ");
            continue;
        }
        break;
    }

    int *arr;
    arr = (int *) malloc(sizeof(int) * n);

    while (1) {
        printf("Вводите эл-ты массива через пробел: ");
        for (i = 0; i < n; i++)
            scanf("%d", (arr+i));

        if (getchar() != '\n')
            while (getchar() != '\n');
        else break;
    }
    /*
    printf("Вводите эл-ты массива через пробел: ");
    for (i = 0; i < n; i++) {
        scanf("%d", (arr+i));
    }
    printf("\n");
    */


    // Сумма отрицательных эл-ов
    int negSum = 0, min = *(arr);
    for (i = 0; i < n; i++) {
        if (*(arr+i) < 0) negSum += *(arr+i);
        if (*(arr+i) < min) min = *(arr+i);
    }
    printf("Сумма отрицательных эл-ов - %d\n", negSum);


    // Колич. эл-ов между первым и последним четными положтельными эл-ми
    int first = -1, last;
    for (i = 0; i < n; i++) {
        if ( (*(arr+i) > 0) && (*(arr+i) % 2 == 0) ) {
            first = i;
            break;
        }
    }
    for (i = n-1; i >= 0; i--) {
        if ( (*(arr+i) > 0) && (*(arr+i) % 2 == 0) ) {
            last = i;
            break;
        }
    }
    if (first == -1)
        printf("В массиве не найдено четных чисел.\n");
    else if (first == last)
        printf("Эл-ов между первым и последним полож. четном - 0\n");
    else
        printf("Эл-ов между первым и последним полож. четном - %d\n",
               (last - first - 1));


    // Удаление минимальных эл-в из массива
    int j;
    for (i = 0; i < n; i++) {
        if (*(arr+i) == min) {
            for (j = i; j < n-1; j++)
                *(arr+j) = *(arr+j+1);
            n--; i--;
        }
    }
    arr = (int *) realloc(arr, sizeof(int) * n);
    printf("Массив после удаления мин. эл-в - ");
    for (i = 0; i < n; i++) {
        printf("%d ", *(arr+i));
    }
    printf("\n");



    return 0;
}
