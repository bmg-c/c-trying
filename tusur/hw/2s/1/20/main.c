#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_FILE_LENGTH 256
#define NotRelated 0
#define Orthogonal 1
#define Parallel 2

#define AXIS_AMOUNT 3
#define VECTORS_AMOUNT 2

void print_vectors(float **vectors) {
    printf("Матрица:\n");

    for (int i = 0; i < VECTORS_AMOUNT; i++) {
        printf("\t");
        for (int j = 0; j < AXIS_AMOUNT; j++) {
            printf("%.2f\t", vectors[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

int read_file(char *file_name, float **vectors) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
        return EXIT_FAILURE;

    for (int i = 0; i < VECTORS_AMOUNT; i++) {
        for (int j = 0; j < AXIS_AMOUNT; j++) {
            if (fscanf(file, "%f", &vectors[i][j]) == 0)
                return EXIT_FAILURE;
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}

float cos_between_vectors(float **vectors) {
    return (vectors[0][0] * vectors[1][0] + vectors[0][1] * vectors[1][1] +
            vectors[0][2] * vectors[1][2]) /
           (powf((powf(vectors[0][0], 2) + powf(vectors[0][1], 2) +
                 powf(vectors[0][2], 2)),
                0.5) *
            powf((powf(vectors[1][0], 2) + powf(vectors[1][1], 2) +
                 powf(vectors[1][2], 2)),
                0.5));
}

int check_vector(float **vectors) {
    float cos_of_angle = cos_between_vectors(vectors);
    printf("%f\n", cos_of_angle);

    if (cos_of_angle == 1.0)
        return Parallel;
    else if (cos_of_angle == 0.0)
        return Orthogonal;
    else
        return NotRelated;
}

int run() {
    char file_name[MAX_FILE_LENGTH];

    printf("Укажите файл с векторами (example.txt): ");
    scanf("%255s", file_name); // file_name уже адрес на начало массива
    while (getchar() != '\n')
        ;
    printf("\n\n");

    float **vectors = (float **)malloc(sizeof(float *) * VECTORS_AMOUNT);
    for (int i = 0; i < VECTORS_AMOUNT; i++)
        vectors[i] = (float *)malloc(sizeof(float) * AXIS_AMOUNT);

    if (read_file(file_name, vectors) == EXIT_FAILURE) {
        printf("Ошибка!\nУказаный файл либо не существует, либо данные указаны "
               "не верно!\n");
        return EXIT_FAILURE;
    }
    print_vectors(vectors);

    switch (check_vector(vectors)) {
    case Parallel:
        printf("Вектора являются параллельными друг к другу.\n");
        break;
    case Orthogonal:
        printf("Вектора являются перпендикулярными друг к другу.\n");
        break;
    default:
        printf("Вектора не относятся друг к другу.\n");
        break;
    }

    for (int i = 0; i < VECTORS_AMOUNT; i++)
        free(vectors[i]);
    free(vectors);

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
