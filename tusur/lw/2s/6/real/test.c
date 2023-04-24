#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int digit(char ch, int digit) { return (ch >> digit) & 1; }

int run() {
    // int x = 123456789, i, p, R = 10, k = 1;
    //
    // while (x > 0) {
    //     p = x % R;
    //     x /= R;
    //     printf("%d ", p);
    // }

    unsigned int y = 200000;
    for (int bit = 0; bit < sizeof(y) * 8; bit++)
        printf("%d", digit(y, bit));
    printf("\n");

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
