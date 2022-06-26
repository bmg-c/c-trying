#include <stdio.h>
#define ARRAYSIZE(x) sizeof(x)/sizeof(x[0])

short int mostCars5mins(short int arr[], short int N);

int main(void) {
   short int n;

   do {
      printf("Введите число измерений: \n");
      scanf("%d", &n);

      if (n < 6 || n > 1440) {
         printf("Удостовертесь, что число измерений больше 5 и меньше 1441\n");
      }
   } while (n < 6 || n > 1440);

   short int measurments[n];
   unsigned short int i;
   short int measure = 0;

   printf("Вводите элементы массива\n");
   for (i = 0; i < n; i++) {
      scanf("%hd", &measurments[i]);
   }

   for (i = 0; i < n; i++) {
      printf("%d - %d\n", i, measurments[i]);
   }

   // unsigned int measurments[] = {10, 20, 30, 40, 50, 10, 50, 60, 30, 20};
   printf("%hd\n", mostCars5mins(measurments, n));

   return 0;
}

short int mostCars5mins(short int arr[], short int N) {
   short int most = 0;
   short int i;

   for ( i = 0 ; i < (N - 4) ; i++) {
      short int cars5mins = arr[i] + arr[i+1] + arr[i+2] + arr[i+3] + arr[i+4];

      if (most < cars5mins) {
         most = cars5mins;
      }
   }

   return most;
}
