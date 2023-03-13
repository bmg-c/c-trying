#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define nrow 3
#define ncol 3

int main() {
    srand(time(NULL));
    int **a = (int **)malloc(sizeof(int *) * nrow);
    for (int i = 0; i < nrow; i++)
        a[i] = (int *)malloc(sizeof(int) * ncol);

    for (int i = 0; i < nrow; i++) {
        for (int j = 0; j < ncol; j++) {
            a[i][j] = rand() % 5 + 1;
            printf("\t%d", a[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < nrow; i++) {
        int targetcol = 0;
        for (int j = 0; j < ncol; j++)
            if (a[i][j] < a[i][targetcol])
                targetcol = j;

        int saddleflag = 1;
        for (int r = 0; r < nrow; r++) {
            if (a[r][targetcol] > a[i][targetcol]) {
                saddleflag = 0;
                break;
            }
        }
        if (saddleflag == 1)
            printf("a[%d][%d]: %d, \t", i, targetcol, a[i][targetcol]);
    }

    for (int i = 0; i < nrow; i++)
        free(a[i]);
    free(a);
    return 0;
}
