#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define ELEMENTS_AMOUNT 10

static void print_file(char* file_name) {
    FILE *binary_file = fopen(file_name, "rb");
    if (binary_file == NULL) {
       printf("Error!");   
       exit(1);             
    }

    printf("%s:\n", file_name);

    for (int i = 0; i < ELEMENTS_AMOUNT * ELEMENTS_AMOUNT; i++) {
        int number;
        fread(&number, sizeof(int), 1, binary_file);

        if (i % ELEMENTS_AMOUNT == 0) {
            printf("\n\t");
        }
        printf("%5d", number);
    }

    printf("\n\n");

    fclose(binary_file);
}

static char* create_file_from_files(char* new_file_name, char* file_name_1, char* file_name_2) {
    FILE *binary_file_1 = fopen(file_name_1, "rb");
    FILE *binary_file_2 = fopen(file_name_2, "rb");  

    FILE *new_binary_file = fopen(new_file_name, "wb");

    for (int i = 0; i < ELEMENTS_AMOUNT * ELEMENTS_AMOUNT; i++) {
        int number_1;
        int number_2;
        fread(&number_1, sizeof(int), 1, binary_file_1);
        fread(&number_2, sizeof(int), 1, binary_file_2);
        if (number_1 < number_2) {
            fwrite(&number_1, sizeof(int), 1, new_binary_file);
        } else {
            fwrite(&number_2, sizeof(int), 1, new_binary_file);
        }
    }

    fclose(binary_file_1);
    fclose(binary_file_2);
    fclose(new_binary_file);

    return new_file_name;
}

static char* generate_file(char* file_name) {
    FILE *binary_file = fopen(file_name, "wb");
    if (binary_file == NULL) {
       printf("Error!");   
       exit(1);             
    }

    for (int i = 0; i <= ELEMENTS_AMOUNT * ELEMENTS_AMOUNT; i++) {
        int random_number = rand() % 100;
        fwrite(&random_number, sizeof(int), 1, binary_file);
    }

    fclose(binary_file);
    
    return file_name;
}

static int run() {
    char* FILE1 = generate_file("FILE1");
    char* FILE2 = generate_file("FILE2");
    char* FILE3 = create_file_from_files("FILE3", FILE1, FILE2);

    print_file(FILE1);
    print_file(FILE2);
    print_file(FILE3);

    return EXIT_SUCCESS;    
}

int main(int argc, char *argv[])
{
    #ifdef _WIN32 // Если Windows, то поменять кодировку страницы
	    system("chcp 65001");
	#endif

    srand(time(NULL)); // Рандомизируем время

    run();
    
    return EXIT_SUCCESS;
}
