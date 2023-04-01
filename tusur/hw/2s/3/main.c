#include <stdio.h>
#include <stdlib.h>

#define MAX_FILENAME_LENGTH 256

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef Node *PNode;

void print_nodes(PNode Head, char *name) {
    PNode TempNode = Head;

    printf("Список %s:\n\t", name);
    while (TempNode != NULL) {
        printf("%d\t->\t", TempNode->value);
        TempNode = TempNode->next;
    }
    printf("\n\n");
}

void add_node(PNode *Head, PNode NewNode) {
    if ((*Head)->value > NewNode->value) {
        NewNode->next = *Head;
        *Head = NewNode;
        return;
    }

    PNode TempNode = *Head;
    while (TempNode->next && TempNode->next->value < NewNode->value) {
        TempNode = TempNode->next;
    }
    if (TempNode->next == NULL) {
        TempNode->next = NewNode;
        return;
    }

    NewNode->next = TempNode->next;
    TempNode->next = NewNode;
}

PNode create_node(int value) {
    PNode NewNode = (PNode)malloc(sizeof(Node));
    NewNode->value = value;
    NewNode->next = NULL;

    return NewNode;
}

PNode read_file_nodes(char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("\nТакого файла не существует!\n");
        exit(1);
    }

    int num_amount = 0;
    fscanf(file, "%d", &num_amount);

    int *nums_arr = (int *)malloc(sizeof(int) * num_amount);
    for (int i = 0; i < num_amount; i++)
        fscanf(file, "%d", &nums_arr[i]);

    PNode Head = create_node(nums_arr[0]);
    for (int i = 1; i < num_amount; i++) {
        PNode NewNode = create_node(nums_arr[i]);
        add_node(&Head, NewNode);
    }

    free(nums_arr);
    return Head;
}

void delete_node(PNode *Head, PNode OldNode) {
    PNode TempNode = *Head; // Записываем реальный адрес в переменную TempNode
                            // При этом не изменяя переменную Head.
    if (*Head == OldNode) {
        *Head = OldNode->next;
        return;
    }
    while (TempNode && (TempNode->next != OldNode)) // Находим эл-т до OldNode
        TempNode = TempNode->next;
    if (TempNode == NULL)
        return;

    TempNode->next = OldNode->next; // Обращаемся к узлу по адресу TempNode
                                    // и записываем ему новый след. элемент
                                    // равный ссылке к узлу после OldNode.
    free(OldNode);
}

PNode find_value(int value, PNode *Head) {
    PNode TempNode = *Head;
    while (TempNode && TempNode->value != value)
        TempNode = TempNode->next;
    if (TempNode == NULL)
        return NULL;

    return TempNode;
}

PNode find_before_value(int value, PNode *Head) {
    if (*Head == NULL)
        return NULL;

    PNode TempNode = *Head;
    while (TempNode->next) {
        if (TempNode->next->value == value)
            break;
        TempNode = TempNode->next;
    }
    if (TempNode->next == NULL)
        return NULL;

    return TempNode;
}

void delete_node_by_value(int value, PNode *Head) {
    if ((*Head)->value == value) {
        delete_node(Head, *Head);
        return;
    }

    PNode TempNode = find_before_value(value, Head);
    if (TempNode == NULL)
        return;

    delete_node(&TempNode, TempNode->next);
}

void delete_max_value(PNode *Head) {
    if (*Head == NULL)
        return;
    if ((*Head)->next == NULL)
        delete_node(Head, *Head);

    PNode TempNode = *Head;
    while (TempNode->next->next)
        TempNode = TempNode->next;
    delete_node(&TempNode, TempNode->next);
}

void change_node_value(int new_value, PNode Node) { Node->value = new_value; }

void replace_node_by_value(int value, int new_value, PNode *Head) {
    if (*Head == NULL || new_value == value)
        return;

    if ((*Head)->value == value) {
        delete_node(Head, *Head);

        PNode NewNode = create_node(new_value);
        add_node(Head, NewNode);

        return;
    }

    if (new_value < value) {
        PNode NewNode = create_node(new_value);
        add_node(Head, NewNode);

        PNode TempNode = find_before_value(value, &NewNode);
        if (TempNode == NULL) {
            delete_node(Head, NewNode);
            return;
        }
        delete_node_by_value(value, &TempNode);
    } else {
        PNode TempNode = find_before_value(value, Head);
        if (TempNode == NULL)
            return;
        delete_node_by_value(value, &TempNode);

        PNode NewNode = create_node(new_value);
        add_node(Head, NewNode);
    }
}

int run() {
    char file_name[MAX_FILENAME_LENGTH];

    printf("Введите название файла: ");
    scanf("%255s", file_name); // \0 в конце
    while (getchar() != '\n')
        ;

    PNode HeadL = read_file_nodes(file_name);

    printf("\nВходные данные:\n");
    print_nodes(HeadL, "L");

    int value = 0;
    printf("\nВведите значение для удаления: ");
    scanf("%d", &value);
    while (getchar() != '\n')
        ;
    delete_node_by_value(value, &HeadL);
    printf("Удален элемент с значением %d.\n", value);
    print_nodes(HeadL, "L");

    delete_max_value(&HeadL);
    printf("\nУдален максимальный элемент.\n");
    print_nodes(HeadL, "L");

    int replace_nums[2];
    printf("\nВведите число для замены (OldNum NewNum): ");
    scanf("%d %d", &replace_nums[0], &replace_nums[1]);
    while (getchar() != '\n')
        ;
    replace_node_by_value(replace_nums[0], replace_nums[1], &HeadL);
    print_nodes(HeadL, "L");

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
