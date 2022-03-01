#include<stdio.h> // include stdio.h library
#include<limits.h>
#include<float.h>

int main(void) {
   int nums[] = {1, 3, 2, 6, 1000, 2, 1};

   int largest = 0;
   for (size_t i = 0; i < 7; i++) {
      largest = largest > nums[i] ? largest : nums[i];
   }

   printf("%d\n", largest);

   return 0;
}
