#include <stdio.h>

int main() {
   printf("|%-10s\n", "555|");
   printf("|%10d|\n", 555);
   printf("|%-10d|\n", 555);
   printf("\n");
   printf("%-15s %4d\n", "Words:", 59);
   printf("%-15s %4d\n", "Letters:", 1004);
   printf("%-15s %4d\n", "Digits:", 8);
}
