#include <stdio.h>
#include <math.h>

int main() {
   int K;
   printf("Введите K:");
   scanf("%d", &K);
   // an = (K + n - 1)(K + n - 1)
   long int S = ((pow(K, 2) + pow(K+30, 2)) / 2) * 31;
   // int S = K;

   printf("\n%d\n", S);

   return 0;
}
