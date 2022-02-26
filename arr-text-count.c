#include <stdio.h>
#define ARRAYSIZE(x) (sizeof(x)/sizeof(*x))

int count(unsigned char T[], int n) {
   unsigned int onlyLetters = 0;
   unsigned int onlyNumbers = 0;
   unsigned int isNum = 0;
   unsigned int isLet = 0;

   for (size_t i = 0; i < n; i++) {
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
            isNum = isNum + 1;
            break;
         case ' ':
         case '.':
            if (isLet > 0) {
               onlyLetters = onlyLetters + 1;
            } else if (isNum > 0) {
               onlyNumbers = onlyNumbers + 1;
            }
            isNum = 0;
            isLet = 0;
            break;
         default:
            isLet = isLet + 1;
            break;
      }

   }


   printf("Only letters words: %d\n", onlyLetters);
   printf("Only numbers words: %d\n", onlyNumbers);

   return 0;
}


int main() {
   unsigned char T[] = {'I', ' ', 'w', 'a', 's', ' ', ' ', '9', '9', '1', ' ', 't', 'o', 'd', 'a', 'y', '.', ' ', 'Y', 'e', 'a', 'h', '.'};

   count(T, ARRAYSIZE(T));

   return 0;
}
