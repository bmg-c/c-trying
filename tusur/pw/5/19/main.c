#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str[25] = "Primer stroki";

    char *word1 = strtok(str, " ");
    char *word2 = strtok(NULL, " ");

    for (int i = 0, is_unique = 0; i < strlen(word1); i++, is_unique = 0) {
        for (int j = 0; j < strlen(word2); j++)
            if (word2[j] == word1[i])
                is_unique = 1;

        if (is_unique == 1)
            printf("Да ");
        else
            printf("Нет ");
    }
}
