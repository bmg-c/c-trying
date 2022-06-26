#include <stdio.h>

int main(void) {
   short N;
   unsigned short right = 0;
   printf("Введите количество чисел: ");
   scanf("%d", &N);

   unsigned short i;
   int arr[N];

   for (i = 0; i < N; i++) {
      printf("Введите %d-е число:", i+1);
      scanf("%d", &arr[i]);
   }

   unsigned short k;
   for (i = 0; i < N; i++) {

      if (i > 3) {
         for (k = 0; k < i - 3; k++) {
            if (((arr[i] * arr[k]) % 29 == 0) && ((arr[i] * arr[k]) != 0)) {
               right += 1;
               printf("%d - %d\n", arr[i], arr[k]);
            }
         }
      }

      if ((i + 4) < N) {
         for (k = i + 4; k < N; k++) {
            // printf("%d\n", (arr[i]));
            if (((arr[i] * arr[k]) % 29 == 0) && ((arr[i] * arr[k]) != 0)) {
               right += 1;
               printf("%d - %d\n", arr[i], arr[k]);
            }
         }
      }

      arr[i] = 0;

   }

   printf("Число пар: %d\n", right);

   return 0;

}
