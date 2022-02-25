#include <stdio.h>

int main() {
   unsigned int n; // Здесь определяем число элементов в массиве

   float B[]; // Здесь определяем n элементов массива
   unsigned int D; // Здесь определяем D

   unsigned float num = 0;
   unsigned int count = 0;

   for (size_t i = 0; i < n; i++) {
      if (B[i] < D && B[i] > 0) {
         num = num + B[i];
         count++;
      }
   }

   printf("%f\n", num/count);

   return 0;
}
