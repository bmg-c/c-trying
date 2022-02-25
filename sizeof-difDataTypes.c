#include <stdio.h>

int main() {
   printf("Integer: %lu\n", sizeof(int));
   printf("Unsigned: %lu\n", sizeof(unsigned int));
   printf("Short: %lu\n", sizeof(short));
   printf("Unsigned short: %lu\n", sizeof(unsigned short));
   printf("Long: %lu\n", sizeof(long));
   printf("Unsigned long: %lu\n", sizeof(unsigned long));
   printf("Char: %lu\n", sizeof(char));
   printf("Float: %lu\n", sizeof(float));
   printf("Double: %lu\n", sizeof(double));
   printf("Long double: %lu\n", sizeof(long double));
   printf("Long float: %lu\n", sizeof(float));
   printf("100 integers array: %lu\n", sizeof(int [100]));
   printf("String <Hello world>: %lu\n", sizeof("Hello world"));
}
