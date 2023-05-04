/* Вариант 7.
 * Дана строка символов. Группы символов, разделенные пробелами (одним или
 * несколькими) и не содержащие пробелов внутри себя, будем называть словами.
 * Подсчитать количество слов, длина которых не превышает заданного числа n. */
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

int words_smaller(char *str, int n) {
    int i = 0;
    while (str[i] == ' ')
        i++;
    if (str[i] == '\0')
        return 0;

    int word_amount = 0, ch_amount = 0, len = strlen(str);
    while (i <= len) {
        if (str[i] == ' ' || str[i] == '\0') {
            if (ch_amount <= n)
                word_amount++;

            if (str[i] == '\0')
                break;
            while (str[i] == ' ')
                i++;
            if (str[i] == '\0')
                break;
            ch_amount = 0;
        }
        i++, ch_amount++;
    }
    return word_amount;
}

int run() {
    char *file_name = (char *)malloc(sizeof(char) * MAX_FILENAME_LENGTH);
    printf("Введите название файла: ");

    int i, ch;
    for (i = 0; (ch = getchar()) != '\n'; i++)
        file_name[i] = (char)ch;
    file_name[i] = '\0';

    int n = 0;
    printf("Введите n: ");
    scanf("%d", &n);

    char *str = read_file(file_name);
    int len = strlen(str);
    printf("%s[end]\n", str);
    for (int i = 0; i < len; i++)
        printf("%d ", str[i]);
    printf("\nstr length: %d\n\n\n", len);

    int word_amount = words_smaller(str, n);

    printf("Количество слов меньше n: %d\n", word_amount);

    free(str);
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
