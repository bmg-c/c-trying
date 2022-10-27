/*
   Домашняя работа 2. Вариант 7
   Задача: проверка и продолжение последовательности.

   Лифанов Иван Сергеевич 422-3.

   Проверял в онлайн-компиляторе и используя gcc и tcc в линуксе.
*/


#include <stdio.h>

int main() {
   // Объявляем переменные n, i
   unsigned char n, i;
   /*
      Объявляем и инициализируем d и x, равными нулю.
      Используем именно этот тип ради получения наибольшей истинной
      последовательности. Используя этот тип можем получить верную
      последовательность до 20-го элемента.
   */
   unsigned long long int d = 0, x = 0;

   // Запрашиваем ввод с клавиатуры последнего элемента последовательности
   // Записываем по адресу n
   printf("Введите до какого элемента показать последовательность: ");
   scanf("%d", &n);

   /*
      Будем считать формулу последовательности такой: x*9 + (i+1) = d

      Из данной нам последовательности можно увидить закономерность:
      если сложить x и d одного элемента, то получим x следующего элемента.
      Используя это мы можем для вычисления следующего x использовать сложение
      нынешнего x с d.
      d мы находим формулой 10*d + 1, которая при каждой итерации будет
      добавлять еще одну однерку к числу.
   */
   for (i = 1; i <= n; i++) {
      d = 10*d + 1;
      x += d;
      // Выводим i-ое равенство последовательности
      printf("%d: %llu*9 + %d = %llu\n", i, x, i + 1, d);
   }


   printf("Программу написал Лифанов Иван Сергеевич 422-3\n");

   return 0; // Отправляем сигнал, что программа завершилась успешно
}
