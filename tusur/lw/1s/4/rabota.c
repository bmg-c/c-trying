#include <stdio.h>
#include <float.h>

int main() {
   system("clear");

   long double x, q, sum, dif;
   float e;
   unsigned int i = 2;

   printf("Введите значение переменной и точность (Пример: x e): ");
   while (scanf("%llf %f", &x, &e) != 2) {
      while (getchar() != '\n');
      system("clear");
      printf("Вы ввели некорректные данные.\n");
      printf("Введите значение переменной и точность (Пример: x e): ");
   }

   q = x*x*x*x*x/48;
   sum = -q;
   x = x*x;
   printf("-%llf", q);

   for (i = 2; ; i++) {
      dif = (x/(i*(i+3)));

      // Находим след. q
      if (q > DBL_MAX / dif) { // Проверяем, переполняется ли q
         printf("\nПроизошло переполнение q\n");
         return 0;
      }
      q *= dif;

      if (e > q) break;

      // Вычисляем sum
      if (i % 2 == 0) {
         if (sum > DBL_MAX - q) { // Проверяем, переполняется ли sum
            printf("\n\nПроизошло переполнение sum\n");
            return 0;
         }
         sum += q;
         printf(" + %llf", q);
      } else {
         if (sum < -DBL_MAX + q) { // Проверяем, переполняется ли sum
            printf("\nПроизошло переполнение sum\n");
            return 0;
         }
         sum -= q;
         printf(" - %llf", q);
      }
   }
   printf(" = %lle\n", sum);

   printf("Сумма чисел с точностью %f и заданной x: %lle. i: %u\n", e, sum, i-1);



   return 0;
}
