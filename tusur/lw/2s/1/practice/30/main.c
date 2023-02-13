#include <stdio.h>
#include <stdlib.h>

#define MAX_FILENAME_LENGTH 256

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

void add_first(PNode* Head, PNode NewNode) { // *. Передаем адрес и по нему
                                             // изменяем значение через *
    NewNode->next = *Head;
    *Head = NewNode;
}

void add_after(PNode NodeAddFrom, PNode NewNode) { // Изменяем значения через "->" => уже
                                        // имеем изменяем его глобально
    NewNode->next = NodeAddFrom->next; // Ставим ссылку на след. после Node
    NodeAddFrom->next = NewNode;
}

void add_before(PNode* Head, PNode NodeAddFrom, PNode NewNode) {
    PNode TempNode = *Head;
    
    if (*Head == NodeAddFrom) {
        add_first(Head, NewNode);
        return;
    }

    while ((TempNode != NULL) && (TempNode->next != NodeAddFrom)) // Находим узел до NodeAddFrom
        TempNode = TempNode->next;

    if (TempNode != NULL) // Т.е если нашли
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
    if (file == NULL) {
        printf("\nТакого файла не существует!\n");
        exit(1);
    }

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
    PNode TempNode = *Head; // Записываем реальный адрес в переменную TempNode
                            // При этом не изменяя переменную Head.
    if (*Head == OldNode) {
        *Head = OldNode->next;
    }
    else {
        while (TempNode && (TempNode->next != OldNode)) // Находим эл-т до OldNode
            TempNode = TempNode->next;
        if (TempNode == NULL)
            return;

        TempNode->next = OldNode->next; // Обращаемся к узлу по адресу TempNode
                                        // и записываем ему новый след. элемент
                                        // равный ссылке к узлу после OldNode
    }
    free(OldNode);
}

void delete_positive(PNode* Head) {
    while ((*Head)->value > 0) {
        delete_node(Head, *Head);
        if (*Head == NULL) return;
    }
    PNode TempNode = *Head;

    while (TempNode->next) { // пока TempNode->next существует
        // printf("\t%d\t", TempNode->value < 0);
        if (TempNode->next->value > 0) {
            delete_node(Head, TempNode->next);
        } else {
            TempNode = TempNode->next;
        }
    }
}

int run() {
    char file_name[MAX_FILENAME_LENGTH];
    printf("Введите название файла: ");
    scanf("%255s", file_name); // \0 в конце
    printf("\n");

    PNode Head = read_file_nodes(file_name);
    print_nodes(Head);

    delete_positive(&Head);
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
