#include <stdio.h>

int main() {
   char not_num[] = "528";
   char num;

   num = (48 - not_num[0]) * (-100) + (48 - not_num[1]) * (-10) + (48 - not_num[2]) * (-1);

   printf("%d\n", (48 - not_num[0]) * (-100) + (48 - not_num[1]) * (-10) + (48 - not_num[2]) * (-1));
   printf("%d\n", num);
}
