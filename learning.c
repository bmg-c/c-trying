#include<stdio.h> // include stdio.h library
#include<limits.h>
#include<float.h>

int main(void) {    
    printf("%30s %12s %28s\n", "", "Size", "Range");

    printf("%-30s %10lu %25d - %d\n", "char or signed char", sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("%-30s %10lu %25d - %d\n", "unsigned char", sizeof(unsigned char), 0, UCHAR_MAX);
    printf("%-30s %10lu %25d - %d\n", "int or signed int", sizeof(int), INT_MIN, INT_MAX);
    printf("%-30s %10lu %25d - %ud\n", "unsigned int", sizeof(unsigned int), 0, UINT_MAX);
    printf("%-30s %10lu %25hd - %hd\n", "short int or short signed int", sizeof(short int), SHRT_MIN, SHRT_MAX);
    printf("%-30s %10lu %25d - %d\n", "unsigned short int", sizeof(unsigned short int), 0, USHRT_MAX);
    printf("%-30s %10lu %25ld - %ld\n", "long int or signed long int", sizeof(long int), LONG_MIN, LONG_MAX);
    printf("%-30s %10lu %25d - %lu\n", "unsigned long int", sizeof(unsigned long int), 0, ULONG_MAX);

    printf("%-30s %10lu %25le - %le\n", "float", sizeof(float), FLT_MIN, FLT_MAX);
    printf("%-30s %10lu %25le - %le\n", "double", sizeof(double), DBL_MIN, DBL_MAX);
    printf("%-30s %10lu %25Le - %Le\n", "long double", sizeof(long double), LDBL_MIN, LDBL_MAX);

    return 0; // return 0 to operating system
}
