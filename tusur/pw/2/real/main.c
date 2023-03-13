#include <stdio.h>
#include <stdlib.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_PRODUCT_NAME_LENGTH 75
#define MAX_COUNTRY_NAME_LENGTH 56

typedef struct {
    char *country;
    char *product_name;
    long long int amount;
} Product;

Product *read_file(char *file_name, int n) {
    Product *arr = (Product *)malloc(sizeof(Product) * n);
    FILE *file = fopen(file_name, "r");

    int ch;
    for (int i = 0; i < n; i++) {
        fgetc(file); // '"'
        int j;
        char *country = (char *)malloc(MAX_COUNTRY_NAME_LENGTH * sizeof(char));
        for (j = 0; (ch = fgetc(file)) != '"'; j++)
            country[j] = (char)ch;
        country[j] = '\0';
        fgetc(file); // ' '

        fgetc(file); // '"'
        char *product_name =
            (char *)malloc(MAX_PRODUCT_NAME_LENGTH * sizeof(char));
        for (j = 0; (ch = fgetc(file)) != '"'; j++)
            product_name[j] = (char)ch;
        product_name[j] = '\0';
        fgetc(file); // ' '

        long long int amount;
        fscanf(file, "%lld", &amount);
        fgetc(file); // '\n'

        arr[i].country = country;
        arr[i].product_name = product_name;
        arr[i].amount = amount;
    }

    fclose(file);
    return arr;
}

void print_arr(Product *arr, int n) {
    printf("Array:\n");
    for (int i = 0; i < n; i++)
        printf("\t%s   %s   %lld\n", arr[i].country, arr[i].product_name,
               arr[i].amount);
    printf("\n\n");
}

void find_desired(Product *arr, int n, char *product_name,
                  long long int min_amount) {
    printf("Found desired products:\n");
    for (int i = 0; i < n; i++) {
        if (arr[i].amount < min_amount)
            continue;
        int are_equal = 1;
        for (int j = 0; j < MAX_PRODUCT_NAME_LENGTH; j++)
            if (arr[i].product_name[j] != product_name[j]) {
                are_equal = 0;
                break;
            }
        if (are_equal)
            printf("\t%s   %s   %lld\n", arr[i].country, arr[i].product_name,
                   arr[i].amount);
    }
    printf("\n\n");
}

int run() {
    int n;
    printf("Enter number of records (n): ");
    scanf("%d", &n);
    while (getchar() != '\n')
        ;

    char file_name[MAX_FILENAME_LENGTH];
    printf("Enter file name (name.txt): ");
    scanf("%255s", file_name);
    while (getchar() != '\n')
        ;

    Product *arr = read_file(file_name, n);
    print_arr(arr, n);

    char product_name[MAX_PRODUCT_NAME_LENGTH + 1]; // '\0'
    printf("Enter desired product name (Product Name): ");
    int i = 0;
    int ch;
    while ((ch = getchar()) != '\n')
        product_name[i++] = (char) ch;

    long long int min_amount;
    printf("Enter min amount (123456789): ");
    scanf("%lld", &min_amount);
    while (getchar() != '\n')
        ;

    printf("\n");
    find_desired(arr, n, product_name, min_amount);

    free(arr);
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
