#include <stdio.h>

int main() {
   // printf("%s %s %d %s %s %d %s\n", "I", "ate", 3, "fish", "that", 1, "day");


   // printf("|%-10s\n", "555|");
   // printf("|%10d|\n", 555);
   // printf("|%-10d|\n", 555);
   // printf("\n");
   // printf("%-15s %4d\n", "Words:", 59);
   // printf("%-15s %4d\n", "Letters:", 1004);
   // printf("%-15s %4d\n", "Digits:", 8);


   // char ch = -66; // От -128 до 127
   // unsigned char uch = 190; // От 0 до 255
   // short j = 'x', k = 190; // От 0 до 255
   //
   // printf("%c -- %d\n", ch, ch);
   // printf("%c -- %d\n", uch, uch);
   // printf("%c, %c\n", j, k);

   // double a = 0.0005;
   // printf("%f\n", a); // Выводит число в обычном виде (по умолчанию до 6 цифр после точки)
   // printf("%g\n", 0.0005); // Выводит число до 4-х цифр после точки. Если же число цифр после точки выше - выводит как пример ниже
   // printf("%g\n", 0.00005); // Выводит число в нормализированном виде, т.е в виде 5e-5, что значит 5*10^-5
   // printf("%e\n", 0.0005); // Выводит число исключительно в нормализированном виде, т.е здесь будет 5.000000e-04
   //
   // a = 0.1234567;
   // printf("%.2f\n", a); // Выводит число с точностью до 2-й цифры после точки
   // printf("%f\n", a); // Выводит число как обычно, с точносью до 6-й цифры, только округляет его до 0.123457, т.к 7>5, т.е ближе к 7-ке, нежели к 6-ке
   // printf("%.7f\n", a); // Выводит число с точностью до 7-й цифры после точки

   // // // Объявление массивов:
   // char vowels[] = {'a', 'e', 'i', 'o', 'u', 'y'};
   //
   // float f_arr[6];
   // f_arr[0] = 25.3;
   // f_arr[4] = 36.4;
   //
   // printf("%c, %.2f, %f\n", vowels[4], f_arr[4], f_arr[3]); // В последнем будет вывод 0.000000, т.е место между не объявленными переменными заполняется нулями
   // // printf("%f\n", f_arr); // Ошибка, так можно делать только со строками


   // // // Объявление строк:
   // // В C строки - это массивы символов, последний элемент которого является 0 (первый элемент из таблицы ASCII)
   // char vowels1[] = {'a', 'e', 'i', 'o', 'u', 'y', '\0'};
   // char vowels2[] = "aeiouy";
   // // Две объявленые строки выше, по факту, одинаковы
   // printf("%s, %s\n", vowels1, vowels2); // Вывод: aeiouy, aeiouy


   // int nums[] = {1, 3, 2, 6, 1000, 2, 1};
   //
   // int largest = 0;
   // for (size_t i = 0; i < 7; i++) {
   //    largest = largest > nums[i] ? largest : nums[i];  //////////////////////////////////////////////////////////////////////
   // }
   //
   // printf("%d\n", largest);


   // int pussy = -14;
   // int *pussy_pointer = &pussy;
   // /* Or:
   // int *pussy_pointer, pussy = -14;
   // pussy_pointer = &pussy;
   // */
   //
   // printf("Address of pussy_pointer - %u\n", pussy_pointer); // The same
   // printf("Address of pussy - %u\n", &pussy); // The same
   // printf("Value of pussy/pussy_pointer - %d\n", *pussy_pointer);


   // printf("Path: C:\\Vowels\\a\n22");


   // int a, b, c;
   // printf("Введите 3 числа\n");
   // scanf("%d,%d,%d", &a, &b, &c);
   // printf("%d,%d,%d\n", a, b, c);


   // char ch;
   //
   // printf("Enter a character: ");
   // ch = getchar();
   //
   // printf("Entered character is: %c\n", ch);
   // // Или
   // putchar(ch);


   int n;
   char ch;

   printf("Введите число: ");
   scanf("%d", &n);

   printf("Введите символ: ");
   scanf("\n%c", &ch);

   printf("%d, %c\n", n, ch);

   return 0;
}
