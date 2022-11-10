#include <stdio.h>
#include <float.h>
#include <math.h>

int main() {
   system("clear");

   long double x, e, q, sum, dif;
   unsigned int i = 2;

   printf("Введите значение переменной и точность (Пример: x e): ");
   while (scanf("%llf %llf", &x, &e) != 2) {
      while (getchar() != '\n');
      system("clear");
      printf("Вы ввели некорректные данные.\n");
      printf("Введите значение переменной и точность (Пример: x e): ");
   }

   q = x*x*x*x*x/48;
   sum = -q;
   x = x*x;
   // printf("-%llf", q);

   for (i = 2; ; i++) {
      dif = (x/(i*(i+3)));
      if (isinf(q*dif)) {
         printf("q переполненна\n");
         return 0;
      }
      q *= dif;
      printf("%d ", isinf(sum + q));
      if (isinf(sum + q)) {
         printf("sum переполненна\n");
         return 0;
      }
      if (e > q) break;

      // Вычисляем sum
      if (i % 2 == 0) {
         sum += q;
         // printf(" + %llf", q);
      } else {
         sum -= q;
         // printf(" - %llf", q);
      }

      // if (isinf(sum)) {
      //    printf("sum переполненна\n");
      //    return 0;
      // }
   }
   printf(" = %llf\n", sum);

   printf("Сумма чисел с точностью %llf и заданной x: %llf. i: %u\n", e, sum, i-1);



   return 0;
}
