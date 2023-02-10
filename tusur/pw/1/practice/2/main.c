#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int min(int* arr, int amount) {
    int min_num = arr[0];
    
    for (int i = 0; i < amount; i++)
        if (min_num > arr[i]) min_num = arr[i];

    return min_num;
}


static int max(int* arr, int amount) {
    int max_num = arr[0];
    
    for (int i = 0; i < amount; i++)
        if (max_num < arr[i]) max_num = arr[i];

    return max_num;
}

static char* create_file_from_files(char* new_file_name, 
        char* file_name_1, char* file_name_2, const int* amounts) {
    FILE *binary_file_1 = fopen(file_name_1, "rb");
    FILE *binary_file_2 = fopen(file_name_2, "rb");  

    FILE *new_binary_file = fopen(new_file_name, "wb");

    int n;
    if (amounts[0] < amounts[1]) {
        n = amounts[0];
    } else {
        n = amounts[1];
    }

    // Добавить элементы по заданию
    for (int i = 0; i < n; i++) {
        int number_1;
        int number_2;
        fread(&number_1, sizeof(int), 1, binary_file_1);
        fread(&number_2, sizeof(int), 1, binary_file_2);
        if (number_1 > number_2) {
            fwrite(&number_1, sizeof(int), 1, new_binary_file);
            fwrite(&number_2, sizeof(int), 1, new_binary_file);
        } else {
            fwrite(&number_2, sizeof(int), 1, new_binary_file);
            fwrite(&number_1, sizeof(int), 1, new_binary_file);
        }
    }


    if (amounts[0] == amounts[1]) {
        return new_file_name;
    }

    // Добавить макс и мин остатка в конец
    int max_file;
    int min_file;

    if (amounts[0] > amounts[1]) {
        int remainder = amounts[0] - amounts[1];
        int slice[remainder];

        for (int i = 0; i < remainder; i++)
            fread(&slice[i], sizeof(int), 1, binary_file_1);           

        max_file = max(slice, remainder);
        min_file = min(slice, remainder);
    } else {
        int remainder = amounts[1] - amounts[0];
        int slice[remainder];

        for (int i = 0; i < remainder; i++)
            fread(&slice[i], sizeof(int), 1, binary_file_2);

        max_file = max(slice, remainder);
        min_file = min(slice, remainder);
    }

    fwrite(&max_file, sizeof(int), 1, new_binary_file);
    fwrite(&min_file, sizeof(int), 1, new_binary_file);
    

    fclose(binary_file_1);
    fclose(binary_file_2);
    fclose(new_binary_file);

    return new_file_name;
}

static char* generate_file(char* file_name, int amount) {
    FILE *binary_file = fopen(file_name, "wb");
    if (binary_file == NULL) {
       printf("Error!");   
       exit(1);             
    }

    for (int i = 0; i <= amount; i++) {
        int random_number = rand() % 100;
        fwrite(&random_number, sizeof(int), 1, binary_file);
    }

    fclose(binary_file);
    
    return file_name;
}

static void print_file(char* file_name, int amount) {
    FILE *binary_file = fopen(file_name, "rb");
    if (binary_file == NULL) {
       printf("Error!");   
       exit(1);             
    }

    printf("%s:\n", file_name);

    for (int i = 0; i < amount; i++) {
        int number;
        fread(&number, sizeof(int), 1, binary_file);

        if (i % 10 == 0) {
            printf("\n\t");
        }
        printf("%5d", number);
    }

    printf("\n\n");

    fclose(binary_file);
}

static int run() {
    int n, m;
    printf("Enter file lengths (n, m): ");
    scanf("%d, %d", &n, &m);

    const int amounts[2] = {n, m};

    char* FILE1 = generate_file("FILE1", amounts[0]);
    char* FILE2 = generate_file("FILE2", amounts[1]);
    print_file(FILE1, amounts[0]);
    print_file(FILE2, amounts[1]);

    if (amounts[0] < amounts[1]) {
        n = amounts[0] * 2 + 2; // по два каждого элемента + макс и мин из остатка
    } else if (amounts[1] < amounts[0]) {
        n = amounts[1] * 2 + 2;
    } else {
        n = amounts[0] * 2;
    }

    const int amount_new_file = n;
    char* FILE3 = create_file_from_files("FILE3", FILE1, FILE2, amounts);
    print_file(FILE3, amount_new_file);

    remove(FILE1);
    remove(FILE2);

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
