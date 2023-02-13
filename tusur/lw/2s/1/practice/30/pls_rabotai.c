#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{
		int data;
		struct node *next;
} node;

node *add(node *top, int d){
	node *newel = (node*)malloc(sizeof(node));
	newel->data = d;
	newel->next = top;
	return newel;
}

void show(node *top){
	if (top == NULL){
		printf("Список пуст\n");
		return;
	}
	while (top){
		if (top->next)
			printf("%5d", top->data);
		else
			printf("%5d\n", top->data);
		top = top->next;
	}
	return;
}

node *Delete(node **top, int n){
	if ((*top) == NULL){
		printf("Error\n");
		return NULL;
	}
	if (n == 1){
		node *temp = (*top)->next;
		(*top)->next = (*top)->next->next;
		free(temp);
	}
	else{
		node *temp = (*top);
		(*top) = (*top)->next;
		free(temp);
	}
	return (*top);
}

node *change_file(node *top){
	node *lifo = top;
	while (top->data > 0){
		lifo = Delete(&top, 0);
	}
	while (top->next){
		if (top->next->data > 0){
			Delete(&top, 1);
		}
		else
			top = top->next;
	}
	if (top->data > 0){
		Delete(&top, 1);
	}
	return lifo;
}

int main(int argc, char *argv[]) {
    node *lifo = NULL;
    int i, n, kol;
    char name[] = "test.txt";
    FILE *f = fopen(name, "r");
	if (f==NULL){
		printf("Файл не найден.\n");
		system("pause");
		exit(0);
	}
	printf("Введите количество чисел в файле:\n");
	scanf("%d", &kol);
    for (i=0; i<kol; i++){
    	fscanf(f, "%d", &n);
    	lifo = add(lifo, n);
    }
    show(lifo);
    lifo = change_file(lifo);
    show(lifo);
    return 0;
}
