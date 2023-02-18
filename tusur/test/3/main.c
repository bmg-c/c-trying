#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 0;
    scanf("%d", &n);

    int** matrix = (int**) malloc(sizeof(int*) * 2);
    for (int i = 0; i < n; i++)
        matrix[i] = (int*) malloc(sizeof(int) * n);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &matrix[i][j]);

    for (int i = 0; i < n - 1; i++)
        printf("%d ", matrix[0][i] * matrix[1][i+1] - matrix[0][i+1] * matrix[1][i]);

    for (int i = 0; i < 2; i++)
        free(matrix[i]);
    free(matrix);

    return 0;
}
