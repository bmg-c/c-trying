#include <stdio.h>
#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))

int main() {
   float X[50]; // создаем массив из 50 вещ-ых чисел
   char count = 0; // Здесь будет счет 3-ек, удовлетворяющих условиям ниже

   for (size_t i = 0; i < ARRAYSIZE(X); i++) {
      if (X[i] == 3 && X[i] > X[i-1] && X[i] < X[i+1]) {
         count++;
      }
   }

   printf("%d\n", count);

   return 0;
}
