#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

#define MAX_FILENAME_LENGTH 256
#define ROW_ELEMENTS_AMOUNT 4
#define MAX_DATE_LENGTH 10
#define MAX_COUNTRY_NAME_LENGTH 56

typedef struct {
    char *country;
    char *date;
    int vouchers;
    long long int cost;
} Flights;

Flights *read_file(char *file_name, int n) {
    Flights *arr = (Flights *)malloc(sizeof(Flights) * n);
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
        char *date = (char *)malloc(MAX_DATE_LENGTH * sizeof(char));
        for (j = 0; (ch = fgetc(file)) != '"'; j++)
            date[j] = (char)ch;
        date[j] = '\0';
        fgetc(file); // ' '

        int vouchers;
        fscanf(file, "%d", &vouchers);
        fgetc(file); // ' '

        long long int cost;
        fscanf(file, "%lld", &cost);
        fgetc(file); // '\n'

        arr[i].country = country;
        arr[i].date = date;
        arr[i].vouchers = vouchers;
        arr[i].cost = cost;
    }

    fclose(file);
    return arr;
}

void print_arr(Flights *arr, int n) {
    printf("Array:\n");
    for (int i = 0; i < n; i++)
        printf("\t%s   %s   %d   %lld\n", arr[i].country, arr[i].date,
               arr[i].vouchers, arr[i].cost);
    printf("\n\n");
}

void find_desired(Flights *arr, int n, char *desired_date,
                  long long int max_cost) {
    printf("Found desired flights:\n");
    for (int i = 0; i < n; i++) {
        if (arr[i].cost > max_cost || arr[i].vouchers == 0)
            continue;
        int are_equal = 1;
        for (int j = 0; j < MAX_DATE_LENGTH; j++)
            if (arr[i].date[j] != desired_date[j]) {
                are_equal = 0;
                break;
            }
        if (are_equal)
            printf("\t%s   %s   %d   %lld\n", arr[i].country, arr[i].date,
                   arr[i].vouchers, arr[i].cost);
    }
    printf("\n\n");
}

int run() {
    int n;
    printf("Enter number of rows (n): ");
    scanf("%d", &n);
    while (getchar() != '\n')
        ;

    char file_name[MAX_FILENAME_LENGTH];
    printf("Enter file name (name.txt): ");
    scanf("%255s", file_name);
    while (getchar() != '\n')
        ;

    Flights *arr = read_file(file_name, n);
    print_arr(arr, n);

    char date[MAX_DATE_LENGTH + 1]; // '\0'
    printf("Enter desired date (dd.mm.yyyy): ");
    scanf("%10s", date);
    while (getchar() != '\n')
        ;

    long long int cost;
    printf("Enter max cost (123456789): ");
    scanf("%lld", &cost);
    while (getchar() != '\n')
        ;

    printf("\n");
    find_desired(arr, n, date, cost);

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
