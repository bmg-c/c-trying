/*
Дана строка символов. Группы символов, разделенные пробелами (одним или
несколькими) и не содержащие пробелов внутри себя, будем называть словами.
Удалить из строки слова, содержащие символы, не являющиеся буквами.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readFile(char *name, int *size) {
    FILE *file = fopen(name, "r");
    while (fgetc(file) != EOF)
        (*size)++;
    fclose(file);

    file = fopen(name, "r");

    char *str = (char *)malloc(sizeof(char) * ((*size) + 1));

    for (int i = 0; i < (*size); i++)
        str[i] = (char)fgetc(file);
    str[(*size)] = '\0';

    fclose(file);

    return str;
}

char *copyStr(char *str, int size) {
    char *temp_str = (char *)malloc(sizeof(char) * (size + 1));
    temp_str = strcpy(temp_str, str);

    return temp_str;
}

char *word(char *str, int size) {
    char *temp = strtok(str, " ,;.!?-");

    return temp;
}

int is_word(char *word) {
    char *x = strpbrk(word, "1234567890");
    if (x)
        return 0;
    return 1;
}

void deleteWord(char **str_2, char *word, int *size) {
    int len = strlen(word);
    len++;
    int temp_size = (*size) - len;

    char *temp_str = (char *)malloc(sizeof(char) * (temp_size + 1));

    for (int i = 0; i <= temp_size; i++, len++) {
        temp_str[i] = (*str_2)[len];
    }

    // printf("%s\n", temp_str);

    (*size) = temp_size;
    (*str_2) = (char *)realloc((*str_2), temp_size);

    for (int i = 0; i <= temp_size; i++) {
        (*str_2)[i] = temp_str[i];
    }
    // printf("%s\n", (*str_2));

    free(temp_str);
}

void rewrite(char **str1, char *str2, int size) {
    (*str1) = (char *)realloc((*str1), size);
    for (int i = 0; i <= size; i++) {
        (*str1)[i] = str2[i];
    }
}

void check(char *str, int size) {
    char *temp_str = copyStr(str, size);
    int answSize = 0;
    char *answer = (char *)malloc(sizeof(char) * (answSize));

    while (1) {
        char *test = word(str, size);
        int len = strlen(test);
        int x = is_word(test);
        printf("str: %s\n", str);
        printf("test: %s\n", test);
        printf("temp_str: %s\n\n", temp_str);

        if (temp_str == NULL || str == NULL || test == NULL) {
            break;
        }

        if (!x) {
            deleteWord(&temp_str, test, &size);
            // printf("str: %s\n", str);
            // printf("test: %s\n", test);
            // printf("temp_str: %s\n\n", temp_str);

            rewrite(&str, temp_str, size);
            // printf("str: %s\n", str);
            // printf("test: %s\n", test);
            // printf("temp_str: %s\n\n", temp_str);
        } else {
            int answStart = answSize;
            answSize += len + 1;
            answer = (char *)realloc(answer, answSize);

            for (int k = answStart; k < answSize - 1; k++)
                answer[k] = test[k - answStart];
            answer[answSize - 1] = ' ';
            answer = strcpy(answer, test);
            deleteWord(&temp_str, test, &size);
            rewrite(&str, temp_str, size);
            printf("answer: ");
            for (int k = 0; k < answSize; k++) {
                printf("%c", answer[k]);
            }
            printf("\n");
        }
        // printf("str: %s\n", str);
        // printf("test: %s\n", test);
        // printf("temp_str: %s\n\n", temp_str);
        if (temp_str == NULL || str == NULL || test == NULL) {
            break;
        }
        // printf("\n\n");
    }
    answer[answSize] = '\0';

    printf("атвет атвет: %s\n", answer);
}

int main() {
    int size = 0;

    char *str = readFile("1", &size);
    printf("%s %d\n", str, size);

    check(str, size);

    // char *temp_str = copyStr(str, size);

    // printf("%s\n", temp_str);

    // char *test = word(str, size);

    // test = word(str, size);

    // int x = is_word(test);

    // deleteWord(&temp_str, test, &size);

    // printf("%s %d\n", test, x);
    // printf("%s\n", temp_str);

    free(str);
    return 0;
}
