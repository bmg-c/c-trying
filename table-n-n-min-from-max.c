#include <stdio.h>
#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))
// #define table[][] {{3,4,2}, {3,1,3}, {3,1,3}}
#define n (3)

int main() {
   unsigned int table[n][n] = {{3,4,2}, {3,1,3}, {3,1,3}}; // 1-я - столбцы, 2-я - строки
   // // unsigned int n = 3;
   //
   // table[2][0] = 3;
   // table[2][1] = 4;
   // table[2][2] = 2;
   //
   // table[1][0] = 1;
   // table[1][1] = 2;
   // table[1][2] = 3;
   //
   // table[0][0] = 3;
   // table[0][1] = 1;
   // table[0][2] = 3;

   unsigned int mins[n];
   unsigned int lines[n];

   for (size_t i = 0; i < n; i++) {
      mins[i] = table[i][i];
      for (size_t k = 0; k < n; k++) {
         if (table[i][k] < mins[i]) {
            mins[i] = table[i][k];
            lines[i] = k + 1;
         }
      }
   }

   unsigned int maxLine, maxColumn, maxNum;
   maxNum = 0;
   for (size_t i = 0; i < n; i++) {
      if (maxNum < mins[i]) {
         maxNum = mins[i];
         maxColumn = i + 1;
         maxLine = lines[i];
      }
   }

   printf("Num: %d\nColumn: %d\nLine: %d\n", maxNum, maxColumn, maxLine);

   return 0;
}
