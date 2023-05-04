/* Вариант 10.
 * Дана строка символов, содержащая ровно два слова. Напечатать только те
 * буквы слов, которые есть только в одном из них (в том числе повторяющиеся).
 * Например, если заданные слова процессор и информация,
 * то ответом должно быть: п е с с и ф м а я. */
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

int is_unique_char_interval(char *str, int start, int end, char ch) {
    for (int i = start; i <= end; i++)
        if (str[i] == ch)
            return 0;

    return 1;
}


char *unique_chars(char *str) {
    int len = strlen(str);

    char *unique_ch_arr = (char*)malloc(sizeof(char) * (len + 1));
    unique_ch_arr[0] = '\0';
    int last_ch = 0;

    int i = 0;

    int start1 = 0;
    while (str[i] != ' ')
        i++;
    int end1 = i - 1;

    int start2 = ++i;
    while (str[i] != '\0')
        i++;
    int end2 = i - 1;

    for (int i = start1; i <= end1; i++)
        if (is_unique_char_interval(str, start2, end2, str[i]) == 1) {
            unique_ch_arr[last_ch++] = str[i];
            unique_ch_arr[last_ch] = '\0';
        }

    for (int i = start2; i <= end2; i++)
        if (is_unique_char_interval(str, start1, end1, str[i]) == 1) {
            unique_ch_arr[last_ch++] = str[i];
            unique_ch_arr[last_ch] = '\0';
        }

    return unique_ch_arr;
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
    printf("%s[end]\n", str);
    printf("str length: %d\n\n\n", len);

    char *unique_chars_arr = unique_chars(str);
    printf("Уникальные символы: %s[end]\n", unique_chars_arr);

    free(unique_chars_arr);
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
