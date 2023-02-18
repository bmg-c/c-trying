#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int reorganize(char* file_name, int* dimensions) {
    FILE *binary_file = fopen(file_name, "rb");
    if (binary_file == NULL) {
       printf("Error!");   
       exit(1);             
    }
    FILE *temp_file = fopen("TEMP", "wb");
    int new_row_amount = 0;

    for (int row_index = 1; row_index <= dimensions[1]; row_index++) {
        int row_arr[dimensions[0]];
        fread(&row_arr, sizeof(int) * dimensions[0], 1, binary_file);

        if (row_arr[dimensions[0] - 1] >= 0) {
            fwrite(&row_arr, sizeof(int) * dimensions[0], 1, temp_file);
            new_row_amount++;
        }
    }
    
    fclose(binary_file);
    fclose(temp_file);

    remove(file_name);
    rename("TEMP", file_name);

    dimensions[1] = new_row_amount;

    return new_row_amount;
}

static char* generate_file(char* file_name, int* dimensions) {
    FILE *binary_file = fopen(file_name, "wb");
    if (binary_file == NULL) {
       printf("Error!");   
       exit(1);             
    }

    for (int i = 0; i < dimensions[1]; i++) {
        int new_record[dimensions[0]]; // массив размера количества столбцов
        for (int j = 0; j < dimensions[0]; j++)
            new_record[j] = rand() % 100 - 50;

        fwrite(&new_record, sizeof(int) * dimensions[0], 1, binary_file);
    }

    fclose(binary_file);
    
    return file_name;
}

static void print_file(char* file_name, int* dimensions) {
    FILE *binary_file = fopen(file_name, "rb");
    if (binary_file == NULL) {
       printf("Error!");   
       exit(1);             
    }

    printf("%s:\n", file_name);

    for (int i = 0; i < dimensions[1]; i++) {
        int record[dimensions[0]]; // массив размера количества столбцов
        fread(&record, sizeof(int) * dimensions[0], 1, binary_file);

        printf("\t");

        for (int j = 0; j < dimensions[0]; j++)
            printf("%5d", record[j]);

        printf("\n");
    }

    printf("\n\n");

    fclose(binary_file);
}

static int run() {
    int n = 5, m = 5;
    printf("Enter matrix dismentions: (n, m): "); // Количество столбцов x строк
    // scanf("%d, %d", &n, &m);

    int* dimensions = malloc(2 * sizeof(int));
    dimensions[0] = n;
    dimensions[1] = m;

    char* FILE1 = generate_file("FILE1", dimensions);
    print_file(FILE1, dimensions);

    dimensions[1] = reorganize(FILE1, dimensions);

    print_file(FILE1, dimensions);

    // remove(FILE1);

    return EXIT_SUCCESS;    
}


int main(int argc, char *argv[]) {
    #ifdef _WIN32
	    system("chcp 65001");
	#endif

    srand(time(NULL)); // Сид ядра рандомизации текущим временем

    if (run() == EXIT_FAILURE) return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}
