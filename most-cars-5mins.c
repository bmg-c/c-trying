#include <stdio.h>
#define ARRAYSIZE(x) sizeof(x)/sizeof(x[0])

int mostCars5mins(unsigned int arr[], unsigned int N);

int main(void) {
   unsigned int measurments[] = {10, 20, 30, 40, 50, 10, 50, 60, 30, 20};
   printf("%u\n", mostCars5mins(measurments, ARRAYSIZE(measurments)));

   return 0;
}

int mostCars5mins(unsigned int arr[], unsigned int N) {
   unsigned int most = 0;
   unsigned int i;

   for ( i = 0 ; i < (N - 4) ; i++) {
      unsigned int cars5mins = arr[i] + arr[i+1] + arr[i+2] + arr[i+3] + arr[i+4];

      if (most < cars5mins) {
         most = cars5mins;
      }
   }

   return most;
}
