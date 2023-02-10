

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Объявляем функцию сортировки
void sort(int n, int *arr);

// Объявляем и инициализируем функцию вывода элементов массива
void printArr(int n, int *arr) {
   unsigned int i;
   for (i = 0; i < n; i++) {
      printf("%3d ", *(arr+i));
   }
   printf("\n");
}

int main() {
   printf("");
   system("clear");
   srand(time(NULL)); // Рандомизируем используя время


   int n = 0, i; // n - размерность массива
   int *arr; // Объявляем указатель на массив arr

   printf("Введите размерность массива: ");
   // Размерность массива - натуральное число
   while (scanf("%d", &n) != 1 || n < 1) {
      while (getchar() != '\n');

      system("clear");
      printf("Вы ввели некорректные данные.\n");
      printf("Введите размерность массива: ");
   }
   arr = (int *) malloc(sizeof(int) * n); // Инициализируем arr размерности n
   printf("%-39s", "Исходный массив: ");
   /*
      Делаем массив с элементами от -100 до 100:
      Если rand()%2 равно 1, то берем rand от 0 до 100 отрицательно
      В противном случае - наоборот
   */
   for (i = 0; i < n; i++) {
      if (rand() % 2) *(arr+i) = -rand()%101;
      else *(arr+i) = rand()%101;
      printf("%3d ", *(arr+i));
   }
   printf("\n\n");

   sort(n, arr);

   printf("Программу написал Лифанов Иван Сергеевич 422-3\n");

   return 0;
}

// Инициализируем функцию сортировки
void sort(int n, int *arr) {
   // comparisons - сравнения
   unsigned int i, j, comparisons = 0;
   // temp - временная переменная, используемая при обмене значений
   int temp;
   /*
      Цикл работает так:
      Сравниваются элементы arr[j] и arr[j+1], в слуачае, если arr[j] больше, то
      они меняются местами. За прохождение n-1 раз по массиву массив будет
      сортирован.
   */
   for (i = 0; i < n-1; i++) {
      for (j = 0; j < n-i-1; j++) { // n-i-1, т.к последние эл-ты сортированны

         if (*(arr+j) > *(arr+j+1)) {
            // Меняем местами значения arr[j] и arr[j+1]
            temp = *(arr+j);
            *(arr+j) = *(arr+j+1);
            *(arr+j+1) = temp;

            printf("%-25c", ' ');
            printArr(n, arr);
         } comparisons++; // Происходит сравнение, прибавляем к счетчика

      }
   }

   printf("\n%-44s", "Сортированный массив: ");
   printArr(n, arr);

   printf("Количество сравнений: %u\n", comparisons);
}
