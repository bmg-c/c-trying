/* Вариант 7.
 * Алгоритм Краскала (стр. 329) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FILENAME_LENGTH 256

int **read_file(char *file_name, size_t *edges_amount_save) {
    size_t edges_amount = 0;
    int value;
    FILE *file = fopen(file_name, "r");
    while (fscanf(file, "%d", &value) != -1)
        edges_amount++;
    edges_amount /= 2;
    fclose(file);

    file = fopen(file_name, "r");
    int **edges = (int **)malloc(sizeof(int *) * edges_amount);
    for (int i = 0; i < edges_amount; i++)
        edges[i] = (int *)malloc(sizeof(int) * 2);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < edges_amount; j++) {
            fscanf(file, "%d", &edges[j][i]);
        }
    }

    (*edges_amount_save) = edges_amount;
    return edges;
}

void print_edges(int **edges, size_t edges_amount, char *message) {
    printf("%s:\n", message);
    for (int i = 0; i < edges_amount; i++)
        printf("\t%d", edges[i][0]);
    printf("\n");
    for (int i = 0; i < edges_amount; i++)
        printf("\t%d", edges[i][1]);
    printf("\n\n");
}

int cyclomatic_number(int **edges, size_t edges_amount) {
    int cyclomatic_number = edges_amount + 1;
    size_t size = 0;
    int *tops_arr = (int *)malloc(sizeof(int) * (edges_amount + 1));

    for (int i = 0; i < edges_amount; i++) {
        for (int j = 0; j < 2; j++) {
            int is_in_arr = 0;
            for (int k = 0; k < size; k++) {
                if (edges[i][j] == tops_arr[k]) {
                    is_in_arr = 1;
                    break;
                }
            }
            if (is_in_arr == 0)
                tops_arr[size++] = edges[i][j];
        }
    }
    cyclomatic_number -= size;

    free(tops_arr);
    return cyclomatic_number;
}

int **algorithm(int **edges, size_t edges_amount, size_t *spanning_tree_size) {
    size_t tops_amount = 0;
    int *tops_arr = (int *)malloc(sizeof(int) * (edges_amount + 1));
    for (int i = 0; i < edges_amount; i++) {
        for (int j = 0; j < 2; j++) {
            int is_in_arr = 0;
            for (int k = 0; k < tops_amount; k++) {
                if (edges[i][j] == tops_arr[k]) {
                    is_in_arr = 1;
                    break;
                }
            }
            if (is_in_arr == 0)
                tops_arr[tops_amount++] = edges[i][j];
        }
    }
    free(tops_arr);

    int **spanning_tree = (int **)malloc(sizeof(int *) * tops_amount);
    for (int i = 0; i < tops_amount; i++)
        spanning_tree[i] = (int *)malloc(sizeof(int) * 2);

    printf("\n\ntops_amount = %lu\n\n", tops_amount);
    size_t k = 0;
    for (size_t i = 0; i < tops_amount - 1 && k < edges_amount; i++)
        do
            spanning_tree[i][0] = edges[k][0],
            spanning_tree[i][1] = edges[k][1], k++;
        while (cyclomatic_number(spanning_tree, i + 1) > 0);
    *spanning_tree_size = tops_amount - 1;

    return spanning_tree;
}

int run() {
    char *file_name = (char *)malloc(sizeof(char) * MAX_FILENAME_LENGTH);
    printf("Введите имя файла (filename): ");
    scanf("%255s", file_name);

    size_t edges_amount = 0;
    int **edges = read_file(file_name, &edges_amount);

    print_edges(edges, edges_amount, "Оригинальный связный граф");

    size_t spanning_tree_size = 0;
    int **spanning_tree = algorithm(edges, edges_amount, &spanning_tree_size);

    print_edges(spanning_tree, spanning_tree_size, "Кратчайший остов");

    free(edges);
    free(spanning_tree);
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
