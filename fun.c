#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "RUS");       

    setlocale(LC_ALL, ".866");

    char str[256];
    scanf("%255s", str);
    for (int i = 0; i < strlen(str); i++)
        str[i] = toupper(str[i]);
    printf("\n%s", str);
}
