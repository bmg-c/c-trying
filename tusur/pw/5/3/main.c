/* Вариант 3.
 * Дана строка символов. Группы символов, разделенные пробелами (одним или
 * несколькими) и не содержащие пробелов внутри себя, будем называть словами.
 * Удалить из строки слова, содержащие символы, не являющиеся буквами. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILENAME_LENGTH 256

char *read_file(char *name) {
    int size = 0;

    FILE *file = fopen(name, "r");
    while (fgetc(file) != EOF)
        size++;
    size--;
    fclose(file);

    file = fopen(name, "r");
    char *str = (char *)malloc(sizeof(char) * (size + 1));

    for (int i = 0; i < size; i++)
        str[i] = (char)fgetc(file);
    str[size] = '\0';

    fclose(file);
    return str;
}

int run() {
    char *file_name = (char *)malloc(sizeof(char) * MAX_FILENAME_LENGTH);
    printf("Введите название файла: ");

    int i, ch;
    for (i = 0; (ch = getchar()) != '\n'; i++)
        file_name[i] = (char)ch;
    file_name[i] = '\0';

    char *str = read_file(file_name);
    int len = strlen(str);
    printf("%s\n", str);
    for (int i = 0; i < len; i++)
        printf("%d ", str[i]);
    printf("\nsize: %d\n\n\n", len);

    i = 0;
    int start = 0, end = 0, is_word = 1;
    while (i < len) {
        if (str[i] == ' ' || str[i] == '\0') {
            if (str[i] == ' ') {
                end = i + 1;
                while (str[end] == ' ' && end < len)
                    end++;
                end--;
            } else
                end = --i;
            printf("is_word: %d\n", is_word);
            printf("start: %d, end: %d\n", start, end);
            printf("size: %d\n", len);
            printf("before change: %s\n", str);

            if (is_word == 0) {
                for (int j = end + 1; j <= len; j++)
                    str[j - (end - start + 1)] = str[j];
                len -= end - start + 1;
                printf("new size: %d\n", len);
                printf("after change: %s\n\n", str);
                i = start;
                is_word = 1;
                continue;
            } else {
                start = end + 1;
                i = start + 1;
                printf("new size: %d\n", len);
                printf("after change: %s\n\n", str);
                continue;
            }
        } else if (str[i] < 65)
            is_word = 0;
        else if (str[i] < 97 || str[i] > 122)
            is_word = 0;
        i++;
    }
    len--; // т.к \0
    str[len] = '\0';
    printf("%s\n", str);
    printf("size: %d, strlen: %lu", len, strlen(str));

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
#ifdef _WIN32
    system("chcp 65001");
#endif

    if (run() == EXIT_FAILURE)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
