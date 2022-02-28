#include<stdio.h> // include stdio.h library
#include<limits.h>
#include<float.h>

int main(void) {
   int num;
   char ch;

   printf("Say a number: ");
   scanf("%d", &num);

   printf("Say a character: ");
   scanf(" %c", &ch);

   printf("\nYou entered num: %d\n", num);
   printf("You entered ch: %c\n", ch);

   return 0; // Показыает, что сработала правильно
}
