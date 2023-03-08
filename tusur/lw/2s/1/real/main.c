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

void add_first(PNode *Head, PNode NewNode) { // *. Передаем адрес и по нему
                                             // изменяем значение через *
    NewNode->next = *Head;
    *Head = NewNode;
}

void add_after(PNode NodeAddFrom,
               PNode NewNode) { // Изменяем значения через "->" => уже
    // имеем изменяем его глобально
    NewNode->next = NodeAddFrom->next; // Ставим ссылку на след. после Node
    NodeAddFrom->next = NewNode;
}

void add_before(PNode *Head, PNode NodeAddFrom, PNode NewNode) {
    PNode TempNode = *Head;

    if (*Head == NodeAddFrom) {
        add_first(Head, NewNode);
        return;
    }

    while ((TempNode != NULL) &&
           (TempNode->next != NodeAddFrom)) // Находим узел до NodeAddFrom
        TempNode = TempNode->next;

    if (TempNode != NULL) // Т.е если нашли
        add_after(TempNode, NewNode);
}

void add_last(PNode *Head, PNode NewNode) {
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
        add_last(&Head, NewNode);
    }

    return Head;
}

void delete_node(PNode *Head, PNode OldNode) {
    PNode TempNode = *Head; // Записываем реальный адрес в переменную TempNode
                            // При этом не изменяя переменную Head.
    if (*Head == OldNode) {
        *Head = OldNode->next;
    } else {
        while (TempNode &&
               (TempNode->next != OldNode)) // Находим эл-т до OldNode
            TempNode = TempNode->next;
        if (TempNode == NULL)
            return;

        TempNode->next = OldNode->next; // Обращаемся к узлу по адресу TempNode
                                        // и записываем ему новый след. элемент
                                        // равный ссылке к узлу после OldNode
    }
    free(OldNode);
}

int divide_linked_list_positive(PNode HeadL, PNode *HeadL1, PNode *HeadL2) {
    if (HeadL == NULL || (*HeadL1) != NULL || (*HeadL2) != NULL)
        return EXIT_FAILURE;

    PNode TempNodeL = HeadL;

    // Создает узел
    int used_positions[2];
    int i = 0; // Используется, чтобы считать прочитанные позиции
    while (TempNodeL && !((*HeadL1) != NULL && (*HeadL2) != NULL)) {
        if (TempNodeL->value > 0 && (*HeadL1) == NULL) {
            *HeadL1 = create_node(TempNodeL->value);
            used_positions[0] = i;
        } else if (TempNodeL->value <= 0 && (*HeadL2) == NULL) {
            *HeadL2 = create_node(TempNodeL->value);
            used_positions[1] = i;
        }

        TempNodeL = TempNodeL->next;
        i++;
    }

    TempNodeL = HeadL;
    PNode TempNodeL1 = *HeadL1;
    PNode TempNodeL2 = *HeadL2;

    i = 0;
    while (TempNodeL) { // пока TempNode существует
        if (TempNodeL->value > 0 && used_positions[0] != i)
            add_last(&TempNodeL1, create_node(TempNodeL->value));
        else if (TempNodeL->value <= 0 && used_positions[1] != i)
            add_last(&TempNodeL2, create_node(TempNodeL->value));

        TempNodeL = TempNodeL->next;
        i++;
    }

    return EXIT_SUCCESS;
}

int run() {
    char file_name[MAX_FILENAME_LENGTH];
    printf("Введите название файла: ");
    scanf("%255s", file_name); // \0 в конце
    printf("\nВходные данные:\n");

    PNode HeadL = read_file_nodes(file_name);
    print_nodes(HeadL, "L");

    PNode HeadL1 = NULL;
    PNode HeadL2 = NULL;
    printf("\n\nВыходные данные:\n");
    if (divide_linked_list_positive(HeadL, &HeadL1, &HeadL2) == EXIT_FAILURE) {
        printf("\nОшибка!\nСписок не существует или два данных списка не "
               "пустые!\n");
        return EXIT_FAILURE;
    }

    print_nodes(HeadL, "L");
    print_nodes(HeadL1, "L1");
    print_nodes(HeadL2, "L2");

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
