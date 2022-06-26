#include <stdio.h>
#define N 4

int main() {
   // Пусть 10 различных сигналов - это цифры от одного до десяти
   // unsigned short signals[N] = {2, 3, 3, 2, 3, 3, 4, 1, 4, 4, 4, 5, 5, 6, 6, 6, 4, 5, 5, 6, 7, 7, 8, 9, 9, 9, 9, 10, 10, 10, 7, 7, 8, 8, 8, 10};
   unsigned short signals[N] = {2, 3, 3, 3};

   unsigned short i, j, highestChar, count = 1;
   unsigned short rare[3][2] = {{0, 0}, {0, 0}, {0, 0}};

   unsigned short highestNum;
   for (i = 1; i < N; i++) {
      if (signals[0] == signals[i]) {
         count++;
      }
   }
   highestNum = count;
   highestChar = 0;
   rare[0][0] = signals[0];
   rare[0][1] = count;


   // printf("i: (), (), (), highestNum, highestChar\n");
   for (i = 1; i < N; i++) {
      // printf("%d: ", i);
      // for (j = 0; j < 3; j++) {
      //    printf("(%d, %d), ", rare[j][0], rare[j][1]);
      // }
      // printf("%d, %d\n", highestNum, highestChar);

      if (signals[i] == rare[0][0]) continue;
      else if (signals[i] == rare[1][0]) continue;
      else if (signals[i] == rare[2][0]) continue;

      count = 0;
      for (j = 0; j < N; j++) {
         if (signals[i] == signals[j]) {
            count++;
         }
      }

      if (rare[1][0] == 0) {
         if (count > highestNum) {
            highestNum = count;
            highestChar = 1;
         }
         rare[1][0] = signals[i];
         rare[1][1] = count;
      } else if (rare[2][0] == 0) {
         if (count > highestNum) {
            highestNum = count;
            highestChar = 2;
         }
         rare[2][0] = signals[i];
         rare[2][1] = count;
      } else {
         if (count < highestNum) {
            rare[highestChar][0] = signals[i];
            rare[highestChar][1] = count;

            highestNum = rare[0][1];
            highestChar = 0;
            for (j = 1; j < 3; j++) {
               if (highestNum < rare[j][1]) {
                  highestNum = rare[j][1];
                  highestChar = j;
               }
            }
         }
      }
   }

   if (rare[2][0] == 0) {
      printf("%d %d\n", rare[0][0], rare[1][0]);
   } else {
      printf("%d %d %d\n", rare[0][0], rare[1][0], rare[2][0]);
   }

   return 0;
}
