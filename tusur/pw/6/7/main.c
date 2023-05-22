/* Вариант 7.
 * Алгоритм Краскала (стр. 329) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int in_arr_index(int *arr, size_t size, int num) {
    for (int i = 0; i < size; i++)
        if (arr[i] == num)
            return i;
    return -1;
}

void delete_from_arr(int *arr, size_t size, int index) {
    for (int i = index + 1; i < size; i++)
        arr[i - 1] = arr[i]

}

int **random_graph_edges(size_t edges_amount, size_t vertices_amount) {
    int **edges = (int **)malloc(sizeof(int *) * edges_amount);
    for (int i = 0; i < edges_amount; i++)
        edges[i] = (int *)malloc(sizeof(int) * 2);

    int *not_used2 = (int *)malloc(sizeof(int) * vertices_amount);
    for (int i = 0; i < vertices_amount; i++)
        not_used2[i] = i + 1;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < vertices_amount; j++)
            size_t not_used_size = vertices_amount;
            int *not_used = (int *)malloc(sizeof(int) * not_used_size);
            for (int i = 0; i < not_used_size; i++)
                not_used[i] = i + 1;

            int vert = rand() % vertices_amount+ 1;

            int index = in_arr_index(not_used, vertices_amount, vert);
            if (index == -1) {

            }

    }

    return edges;
}

void print_edges(int **edges, size_t edges_amount) {
    printf("Ребра:\n");
    for (int i = 0; i < edges_amount; i++)
        printf("\t%d", edges[i][0]);
    printf("\n");
    for (int i = 0; i < edges_amount; i++)
        printf("\t%d", edges[i][1]);
}

int **algorithm(int **edges, size_t edges_amount) {

}

int run() { 
    int edges_amount = 7, vertices_amount = 5;
    int **edges = random_graph_edges(edges_amount, vertices_amount);

    print_edges(edges, edges_amount);

    return EXIT_SUCCESS; }

int main(int argc, char *argv[]) {
#ifdef _WIN32
    system("chcp 65001");
#endif

    srand(time(NULL));

    if (run() == EXIT_FAILURE)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
