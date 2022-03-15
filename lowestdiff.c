#include<stdio.h>
#define ARRAYSIZE(x) sizeof(x)/sizeof(x[0])
int lowestDiff(int arr[], unsigned int n);

int main(void) {
   int numbers[] = {10, 1, -10, 8, 90, 50, 4, -5, 0, -2};
   // printf("%d\n", ARRAYSIZE(numbers));
   lowestDiff(numbers, ARRAYSIZE(numbers));
   return 0;
}


int lowestDiff(int arr[], unsigned int n) {
   unsigned int lowestDiff;
   unsigned int i;

   if (arr[0] > arr[1]) {
      lowestDiff = arr[0] -arr[1];
   } else {
      lowestDiff = arr[1] - arr[0];
   }

   for (i = 0; i < (n - 1); i++) {
      unsigned int k;

      for (k = (i + 1); k < n; k++) {
         if (arr[i] > arr[k]) {

            if ( lowestDiff > (arr[i] - arr[k]) ) {
               lowestDiff = arr[i] - arr[k];
            }

         } else {

            if ( lowestDiff > (arr[k] - arr[i]) ) {
               lowestDiff = arr[k] - arr[i];
            }

         }
      }

   }

   printf("i+1 : %-10s;%10s : %-10s;%10s%9c\n", "k+1", "arr[i]", "arr[k]", "diff", ';');

   for (i = 0; i < (n - 1); i++) {
      unsigned int k;

      for (k = (i + 1); k < n; k++) {
         if (lowestDiff == (arr[k] - arr[i]) || lowestDiff == (arr[i] - arr[k])) {
            printf("%-3d : %-10d;%10d : %-10d;%10d\n", i+1, k+1, arr[i], arr[k]);
         }
      }
   }

}
