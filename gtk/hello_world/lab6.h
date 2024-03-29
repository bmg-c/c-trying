#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>

static void sort_sum (int n, int **arr, int *sum);

int func (GtkWidget *widget, gpointer data) {
    #ifdef _WIN32 // Если Windows, то поменять кодировку страницы
	    system ("chcp 65001");
	#endif
    srand (time(NULL)); // Рандомизируем функцию rand в настоящее время

    // // Инициализируем переменные, а также запрашиваем ввод n (размерности)
    system ("clear");
    g_print ("n = %s\n", (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (data)) ));
    int n = atoi(gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (data)));
    int i, j, k;
    if (n < 0) { // Пусть массив должен быть больше или равен 0
        g_print ("Данные некорректны.\nПопробуйте еще раз.");
        return 0;
    }

    // Определяем главную матрицу
    int **arr = (int **) malloc (sizeof (int *) * n); // Выделяем память под строки
    for (i = 0; i < n; i++) // Выделяем память под элементы строк
        arr[i] = (int *) malloc (sizeof (int) * n);

    // Генерируем целые числа в элементы матрицы
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            arr[i][j] = rand() % 100;
        }
    }


    // Определяем и инициализируем нулями массив сумм элементов строк
    int *sum = (int *) malloc (sizeof (int) * n);
    for (i = 0; i < n; i++)
        sum[i] = 0;

    // Выводим матрицу и строки, в которых нет повторяющихся элеметов
    unsigned char flag = 1; // Являются ли элементы строки неубывающими
    for (i = 0; i < n; i++) {
        g_print ("\n%4d ", arr[i][0]);
        sum[i] += arr[i][0];

        for (j = 1; j < n; j++) {
            if (arr[i][j-1] >= arr[i][j]) flag = 0; // Если прошлый больше
            sum[i] += arr[i][j];

            g_print ("%4d ", arr[i][j]);
        }
        if (flag == 1) g_print (" <--  %d, неубывающая", sum[i]);
        else {
            flag = 1;
            g_print (" <--  %d", sum[i]);
        }
    }
    



    // // Сортировка сумм элементов строки и вывод нового порядка в массив

    g_print ("\n\n\nХод сортировки строк:\n");
    sort_sum(n, arr, sum);
    

    // Выводим матрицу
    g_print ("\n\n\nСортированная сумма:\n");
    for (i = 0; i < n; i++) {
        g_print("%4d ", sum[i]);
    }

    g_print ("\n\n\nСортированная матрица:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            g_print("%4d ", arr[i][j]);
        }
        g_print("  <--  %d", sum[i]);
        g_print("\n");
    }


    g_print ("\n\nПрограмму написал Лифанов Иван Сергеевич 422-3\n");

    return 0;
}



static void sort_sum (int n, int **arr, int *sum) {
    int i, j, mn = n-1;
    int el;

    int temp;
    int *temp_arr = (int *) malloc (sizeof (int) * n);
    
    for (i = 0; i < n; i++) {
        el = 0; // Нынешний минимальный элемент в промежутке [0, mn]

        for (j = 0; j <= mn; j++) {
            if (sum[el] > sum[j]) el = j;
        }

        // Вывод прогресса сортировки, можно убрать
        g_print ("%d\n", el+1);
        for (j = 0; j < n; j++) {
            g_print ("%d ", sum[j]);
        }
        g_print ("\n\n");

        // Меняем местами элементы минимальный и последний элементы
        temp = sum[el];
        sum[el] = sum[mn];
        sum[mn] = temp;
        // Меняем местами строки согласно обмене суммы
        temp_arr = arr[el];
        arr[el] = arr[mn];
        arr[mn] = temp_arr;

        mn--;
    }
}