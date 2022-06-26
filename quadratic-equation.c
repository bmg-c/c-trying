#include <stdio.h>
#include <math.h>
#include <string.h>
#define STRSIZE(x) (sizeof(x)/sizeof(x[0]) - 1)

int quad(char *str) {
   int a = 1, b = 1, c = 1;
   unsigned int i, k;

   int num = 1;
   char numStr[strlen(str)];
   unsigned int len = 0;
   unsigned char state = 0;

   // sscanf(numStr, "%04d", &num);

   for (i = 0; i < strlen(str); i++) {
      if (str[i] == 'x') {
         sscanf(numStr, "%04d", &num);
         if (str[i+1] == '^') {
            i += 2;
            state += 1;
         }

         memset(numStr,0,sizeof(numStr));

         len = 0;
      } else {
         numStr[len] = str[i];
         len++;
      }
      // printf("%s   ", numStr);
   }

   sscanf(numStr, "%04d", &num);
   c = num;
   memset(numStr,0,sizeof(numStr));
   len = 0;

   printf("a - %d; b - %d; c - %d;\n", a, b, c);

   return 0;
}

int main(void) {
   char str[] = "x^2 - 3x + 2";
   quad(str);

   // char str[] = "x^2 - 3333x + 2 = 0";
   // quad(str);

   return 0;
}
