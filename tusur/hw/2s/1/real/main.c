#include <stdio.h>
#include <stdlib.h>

#define MAX_FILE_LENGTH 256

#define ELEMENTS_AMOUNT 3
#define EQUATIONS_AMOUNT 3

void print_system(double** matrix, double* free_variables) {
    printf("Расширенная матрица:\n");

    for (int i = 0; i < EQUATIONS_AMOUNT; i++) {
        printf("\t");
        for (int j = 0; j < ELEMENTS_AMOUNT; j++) {
            printf("%.2lf\t", matrix[i][j]);
        }
        printf("|\t%.2lf\n", free_variables[i]);
    }

    printf("\n");
}

void print_matrix(double** matrix) {
    printf("Матрица:\n");

    for (int i = 0; i < EQUATIONS_AMOUNT; i++) {
        printf("\t");
        for (int j = 0; j < ELEMENTS_AMOUNT; j++) {
            printf("%.2lf\t", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

int read_file(char* file_name, double** matrix, double* free_variables) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL)
        return EXIT_FAILURE;

    for (int i = 0; i < EQUATIONS_AMOUNT; i++) {
        for (int j = 0; j < ELEMENTS_AMOUNT; j++) {
            if (fscanf(file, "%lf", &matrix[i][j]) == 0)
                return EXIT_FAILURE;
        }
        if (fscanf(file, "%lf", &free_variables[i]) == 0)
            return EXIT_FAILURE;
    }

    fclose(file);
    return EXIT_SUCCESS;
}

// Нахождение через правило Саррюса
double matrix_determinant(double** matrix) {
    float determinant = 0;

    // Произведения элементов на главной диагонали и ей паралельных
    for (int i = 0; i < ELEMENTS_AMOUNT; i++) {
        float temp = 1;
        for (int j = 0; j < ELEMENTS_AMOUNT; j++) {
            int element = i + j;
            if (element >= ELEMENTS_AMOUNT)
                element -= ELEMENTS_AMOUNT;

            temp *= matrix[j][element];
        }
        determinant += temp;
    }

    // Произведения элементов на побочной диагонали и ей паралельных
    for (int i = 0; i < ELEMENTS_AMOUNT; i++) {
        float temp = 1;
        for (int j = 0; j < ELEMENTS_AMOUNT; j++) {
            int element = i - j;
            // Если меньше нуля - начать вычитывать с конца
            if (element < 0)
                element += ELEMENTS_AMOUNT;

            temp *= matrix[j][element];
        }
        determinant -= temp;
    }
    
    // printf("\n%lf\n", determinant);

    return determinant;
}

int system_solution(double** matrix, double* free_variables, double* solution) {
    double main_determinant = matrix_determinant(matrix);
    if (main_determinant == 0)
        return EXIT_FAILURE;
    double secondary_determinants[ELEMENTS_AMOUNT];

    for (int i = 0; i < ELEMENTS_AMOUNT; i++) {
        double** secondary_matrix = (double**) malloc(sizeof(double*) * EQUATIONS_AMOUNT);
        for (int i = 0; i < EQUATIONS_AMOUNT; i++)
            secondary_matrix[i] = (double*) malloc(sizeof(double) * ELEMENTS_AMOUNT);


        for (int j = 0; j < EQUATIONS_AMOUNT; j++)
            for (int k = 0; k < ELEMENTS_AMOUNT; k++)
                secondary_matrix[j][k] = matrix[j][k];

        for (int j = 0; j < EQUATIONS_AMOUNT; j++)
            secondary_matrix[j][i] = free_variables[j];


        secondary_determinants[i] = matrix_determinant(secondary_matrix);
        

        for (int j = 0; j < EQUATIONS_AMOUNT; j++)
            free(secondary_matrix[j]);
        free(secondary_matrix);
    }

    for (int i = 0; i < ELEMENTS_AMOUNT; i++) {
        solution[i] = secondary_determinants[i] / main_determinant;
    }

    return EXIT_SUCCESS;
}

int run() {
    char file_name[MAX_FILE_LENGTH];
    printf("Пример файла (не включая /* ... */):\n\t/* \tX\tY\tZ\tЧему равно */\n\t\t1\t2\t3\t10\n\t\t4\t5\t6\t20\n\t\t7\t8\t9\t30\n\n");

    printf("Укажите файл с СЛАУ (example.txt): ");
    scanf("%255s", file_name); // file_name уже адрес на начало массива
    printf("\n\n");

    double** matrix = (double**) malloc(sizeof(double*) * EQUATIONS_AMOUNT);
    for (int i = 0; i < EQUATIONS_AMOUNT; i++)
        matrix[i] = (double*) malloc(sizeof(double) * ELEMENTS_AMOUNT);
    
    double* free_variables = (double*) malloc(sizeof(double) * EQUATIONS_AMOUNT);

    if (read_file(file_name, matrix, free_variables) == EXIT_FAILURE) {
        printf(
            "Ошибка!\nУказаный файл либо не существует, либо данные указаны не верно!\n"
        );
        return EXIT_FAILURE;
    }

    print_matrix(matrix);
    print_system(matrix, free_variables);


    double* solution = (double*) malloc(sizeof(double*) * ELEMENTS_AMOUNT);
    if (system_solution(matrix, free_variables, solution) == EXIT_FAILURE) {
        printf("Ошибка!\nДанную систему невозможно решить методом Крамера!");
        return EXIT_FAILURE;
    }
    printf("\nРешение:\n\t");
    for (int i = 0; i < ELEMENTS_AMOUNT; i++) {
        printf("%lf\t", solution[i]);
    }

    for (int i = 0; i < 3; i++)
        free(matrix[i]);
    free(matrix);
    free(free_variables);
    free(solution);

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
