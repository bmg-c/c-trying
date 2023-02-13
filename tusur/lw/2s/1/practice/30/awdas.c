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
	while (top){
		if (top->next)
			printf("%5d", top->data);
		else
			printf("%5d\n", top->data);
		top = top->next;
	}
}

void Delete(node **top, int n){
	if ((*top) != NULL && n == 1){
		node *temp = (*top)->next;
		(*top)->next = (*top)->next->next;
		free(temp);
	}
	else{
		printf("Error");
		return;
	}
	return;
}

void change_file(node *top){
	if (top->data > 0)
		Delete(&top, 0);
	while (top->next){
		if (top->next->data > 0)
			Delete(&top, 1);
		else
			top = top->next;
	}
	return;
}

int main(int argc, char *argv[]) {
    system("chcp 65001");
    node *lifo = NULL;
    int i, n;
    char name[] = "text.txt";
    FILE *f = fopen(name, "r");
	if (f==NULL){
		printf("Файл не найден.\n");
		system("pause");
		exit(0);
	}
    for (i=0; i<7; i++){
    	fscanf(f, "%d", &n);
    	lifo = add(lifo, n);
    }
    show(lifo);
    change_file(lifo);
    show(lifo);
    system("pause");
    return 0;
}