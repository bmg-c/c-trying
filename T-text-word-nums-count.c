#include <stdio.h>
#define STRSIZE(x) (sizeof(x)/sizeof(x[0]) - 1) // (-1), потому что строка - это массив символов с последним элементом в массиве "\0"

int count(char *T, unsigned int n, char *name) {
   unsigned int words = 0, numbers = 0, isNum = 0, isLet = 0, i = 0;

   for ( ; i < n; i++) {
      switch (T[i]) {
         case '0':
         case '1':
         case '2':
         case '3':
         case '4':
         case '5':
         case '6':
         case '7':
         case '8':
         case '9':
            isNum += 1;
            // printf("%c - %d\n", T[i], i);
            break;
         case ' ':
         case '.':
            if (isLet > 0 && isNum > 0) {
               // printf("%d - %d\n", T[i], i);
               continue;
            }
            if (isLet > 0) {
               words += 1;
            } else if (isNum > 0) {
               numbers += 1;
            }
            isLet = isNum = 0;
            break;
         default:
            isLet += 1;
            // printf("%c - %d", T[i], i);
            // printf(", isLet = %d \n", isLet);
            break;
      }
   }

   if (isLet > 0) {
      words += 1;
   } else if (isNum > 0) {
      numbers += 1;
   }

   printf("%s\n", name);
   printf("Words: %d\n", words);
   printf("Numbers: %d\n\n", numbers);


   return 0;
}

int main(void) {
   char T1[] = " I was going to call 911 but the police    would make it even worse.    So i  didnt call em this 1 day  .  ";
   count(T1, STRSIZE(T1), "T1");
   // 20 words, 2 nums, 107 symbols;

   char T2[] = "My family left me. Im sad now";
   count(T2, STRSIZE(T2), "T2");
   // 7 words, 0 nums,

   return 0;
}
