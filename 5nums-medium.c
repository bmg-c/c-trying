#include <stdio.h>

int main(void) {
   float num, sum = 0;
   char i;
   for (i = 1; i <= 5; i++) {
      printf("Введите %d число: ", i);
      scanf("%f", &num);
      sum += num;
      printf("Среднее арифметическое сейчас - %f\n\n", sum/i);
   }

   return 0;
}
