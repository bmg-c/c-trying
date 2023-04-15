#include "nodes.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_FILENAME_LENGTH 256

int run(int argc, char *argv[]) {
    char file_name[MAX_FILENAME_LENGTH];
    printf("Введите название файла: ");
    scanf("%255s", file_name); // \0 в конце
    while (getchar() != '\n') // Очищаем буффер
        ;

    // if (argv[1] == NULL) {
    //     printf("Не указано название файла.\n");
    //     return EXIT_FAILURE;
    // }
    // char *file_name = argv[1];

    PNode HeadL = read_file_nodes(file_name);
    if (HeadL == NULL) {
        printf(
            "Список пустой или не правильно заданы значения в входном файле");
        return EXIT_FAILURE;
    }

    printf("\nВходные данные:\n");
    print_nodes(HeadL, "L");

    int value = 0;
    printf("\nВведите значение для удаления: ");
    scanf("%d", &value);
    while (getchar() != '\n') // Очищаем буффер
        ;
    delete_node_by_value(value, &HeadL);
    printf("Удален элемент с значением %d.\n", value);
    print_nodes(HeadL, "L");

    delete_max_value(&HeadL);
    printf("\nУдален максимальный элемент.\n");
    print_nodes(HeadL, "L");

    change_node_value(7, &HeadL, &HeadL);
    ;
    printf("\nЗначение головы списка изменено на 7\n");
    print_nodes(HeadL, "L");

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
#ifdef _WIN32
    system("chcp 65001");
#endif

    if (run(argc, argv) == EXIT_FAILURE)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
