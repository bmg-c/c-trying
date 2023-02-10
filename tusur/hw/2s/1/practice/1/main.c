#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//	Напишите программу, которая находит определитель произвольной матрицы 3-го порядка.
// чтение текстового файла и записывание матрицы 
int** create_matrix_from_file(char*name){
	FILE*f;
	if((f=fopen(name,"r"))==NULL){// проверка на наличие файла.
		printf("File not found.");
		system("PAUSE");
		return 0;
	}
	int i;
	int n,j;
	int **x=NULL;
	fscanf(f,"%d",&n);// считыванием размерность матрицы из файла .
	x=(int**)malloc(sizeof(int*)*n);// выделение памяти для матрицы 
	for(i=0;i<n;i++){
		x[i]=(int*)malloc(sizeof(int)*n);
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			fscanf(f,"%d",&x[i][j]); // записывание в матрицу числа из текстового фалйа.
		}
	fclose(f);
	printf("Прочитана матрица:\n");
	//вывод матрицы на экран 
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			printf("%3d",x[i][j]);
		printf("\n");}
return x;
}

// функция подсчёта определителя 
int opredelitel(int **x){
	int O;
	O=x[0][0]*x[1][1]*x[2][2]+x[0][1]*x[1][2]*x[2][0]+x[0][2]*x[1][0]*x[2][1]
		-x[0][2]*x[1][1]*x[2][0]-x[0][0]*x[1][2]*x[2][1]-x[0][1]*x[1][0]*x[2][2];// счёт определителя при помощи правила треугольника
	return O;
}


int main(int argc, char *argv[]) {
	system("chcp 65001");
	int n=3;
	char name[25];
	
	printf("Введите имя файла: ");
	scanf("%s",name);
	create_matrix_from_file(name);
	printf("Определитель матрицы: %d\n",opredelitel(create_matrix_from_file(name)));


	system("PAUSE");
		
	return 0;
}