#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10

int main() {
    int s[N];
    int d = 0;
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        s[i] = rand() % 10 + 1;
        printf("%d\t", s[i]);
    }

    for (int i = 0; i < N; i++)
        if (s[i] == 10) {
            int temp = s[i];
            s[i] = s[d];
            s[d] = temp;
            // s[i] = s[d];
            // s[d] = 10;
            d++;
        }

    printf("\n%d", d);
    return 0;
}
