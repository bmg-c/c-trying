#include <stdio.h>
int isPrime(unsigned int n);

int main(void) {
   unsigned int n;
   unsigned char cond = 1;
   do {
      printf("Введите число: ");
      scanf("%d", (int)&n);

      if (n > 2) {
         cond = 0;
      } else {
         printf("Введите целое число, которое больше числа 2\n");
      }
   } while (cond);

   isPrime(n);

   return 0;
}

int isPrime(unsigned int n) {
   switch (n) {
      case 3:
      case 5:
      case 7:
         printf("%d - не простое число\n", n);
         return 0;
   }
   if ( n % 2 != 0 && n % 3 != 0 && n % 5 != 0 && n % 7 != 0 ) {
      printf("%d - не простое число\n", n);
   } else {
      printf("%d - простое число\n", n);
   }

}
