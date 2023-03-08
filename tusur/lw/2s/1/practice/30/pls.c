#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef Node* PNode;

void print_nodes(PNode Head) {
    PNode TempNode = Head;

    printf("Список:\n\t");
    while (TempNode != NULL) {
        printf("%d\t->\t", TempNode->value);
        TempNode = TempNode->next;
    }
    printf("\n\n");
}

void add_first(PNode* Head, PNode NewNode) {
    NewNode->next = *Head;
    *Head = NewNode;
}

void add_after(PNode NodeAddFrom, PNode NewNode) {
    NewNode->next = NodeAddFrom->next;
    NodeAddFrom->next = NewNode;
}

void add_before(PNode* Head, PNode NodeAddFrom, PNode NewNode) {
    PNode TempNode = *Head;
    
    if (*Head == NodeAddFrom) {
        add_first(Head, NewNode);
        return;
    }

    while ((TempNode != NULL) && (TempNode->next != NodeAddFrom))
        TempNode = TempNode->next;

    if (TempNode != NULL)
        add_after(TempNode, NewNode);
}

void add_last(PNode* Head, PNode NewNode) {
    PNode TempNode = *Head;

    if (*Head == NULL) {
        add_first(Head, NewNode);
        return;
    }

    while (TempNode->next != NULL)
        TempNode = TempNode->next;

    add_after(TempNode, NewNode);
}

PNode create_node(int value) {
    PNode NewNode = (PNode) malloc(sizeof(Node));
    NewNode->value = value;
    NewNode->next = NULL;

    return NewNode;
}

PNode read_file_nodes(char* file_name) {
    FILE* file = fopen(file_name, "r");

    int num_amount = 0;
    fscanf(file, "%d", &num_amount);

    int* nums_arr = (int*) malloc(sizeof(int) * num_amount);
    for (int i = 0; i < num_amount; i++)
       fscanf(file, "%d", &nums_arr[i]);


    PNode Head = create_node(nums_arr[0]);
    for (int i = 1; i < num_amount; i++) {
        PNode NewNode = create_node(nums_arr[i]);
        add_last(&Head, NewNode);
    }

    return Head;
}

void delete_node(PNode* Head, PNode OldNode) {
    PNode TempNode = *Head;
    if (*Head == OldNode) {
        *Head = OldNode->next;
    }
    else {
        while (TempNode && (TempNode->next != OldNode))
            TempNode = TempNode->next;
        if (TempNode == NULL)
            return;

        TempNode->next = OldNode->next;
    }
    free(OldNode);
}

int run() {
    char file_name[256];
    printf("Введите название файла: ");
    scanf("%255s", file_name);
    printf("\n");

    PNode Head = read_file_nodes(file_name);
    print_nodes(Head);

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    #ifdef _WIN32
	    system("chcp 65001");
	#endif

    if (run() == EXIT_FAILURE)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
