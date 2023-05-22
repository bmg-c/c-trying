#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256

typedef struct Node {
    int value;
    struct Node *right;
    struct Node *left;
} Node;

typedef Node *PNode;

PNode create_node(int value) {
    PNode NewNode = (PNode)malloc(sizeof(Node));
    NewNode->value = value;
    NewNode->left = NULL;
    NewNode->right = NULL;

    return NewNode;
}

void insert(PNode *Root, int value) {
    // if (*Root == NULL) {
    //     *Root = create_node(value);
    //     return;
    // }
    //
    // if (value >= (*Root)->value)
    //     insert(&((*Root)->right), value);
    // else
    //     insert(&((*Root)->left), value);

    if (*Root == NULL) {
        *Root = create_node(value);
        return;
    }

    PNode TempNode = *Root;
    while (TempNode != NULL) {
        if (value >= TempNode->value) {
            if (TempNode->right == NULL) {
                TempNode->right = create_node(value);
                return;
            } else
                TempNode = TempNode->right;
        } else {
            if (TempNode->left == NULL) {
                TempNode->left = create_node(value);
                return;
            } else
                TempNode = TempNode->left;
        }
    }
}

PNode read_file_nodes(char *file_name) {
    PNode Root = NULL;

    FILE *file = fopen(file_name, "r");
    if (file == NULL)
        return Root;

    int value;
    size_t size = 0;
    while (fscanf(file, "%d", &value) != -1)
        size++;
    printf("size: %lu\n", size);

    fclose(file);

    if (size == 0)
        return Root;

    file = fopen(file_name, "r");
    for (int i = 0; i < size; i++) {
        value = 0;
        fscanf(file, "%d", &value);
        insert(&Root, value);
    }

    fclose(file);
    return Root;
}

typedef struct Tree {
    Node *node;
    struct Tree *next;
} Tree;
typedef Tree *PTree;

PTree create_tree(PNode Node) {
    PTree NewNode = (PTree)malloc(sizeof(Tree));
    NewNode->node = Node;
    NewNode->next = NULL;

    return NewNode;
}

void add_tree(PTree *Head, PNode Node) {
    if (*Head == NULL) {
        *Head = create_tree(Node);
        return;
    }
    PTree TempTree = *Head;
    while (TempTree->next != NULL)
        TempTree = TempTree->next;

    TempTree->next = create_tree(Node);
}

PNode remove_tree(PTree *Head) {
    PTree TempTree = *Head;
    *Head = (*Head)->next;

    PNode Node = TempTree->node;
    free(TempTree);

    return Node;
}

void print_nodes(PNode Root) {
    PTree Tree = NULL;
    add_tree(&Tree, Root);

    while (Tree != NULL) {
        PNode TempNode = remove_tree(&Tree);
        printf("%d ", TempNode->value);

        if (TempNode->left != NULL)
            add_tree(&Tree, TempNode->left);
        if (TempNode->right != NULL)
            add_tree(&Tree, TempNode->right);
    }
}

int run(int argc, char *argv[]) {
    char file_name[MAX_FILENAME_LENGTH];
    printf("Введите название файла: ");
    scanf("%255s", file_name);
    while (getchar() != '\n')
        ;

    PNode Root = read_file_nodes(file_name);
    if (Root == NULL) {
        printf("\n\nОшибка!\nФайл либо пустой, либо не существует.\n");
        return EXIT_FAILURE;
    }

    print_nodes(Root);

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
#ifdef _WIN32
    system("chcp 65001");
#endif

    if (run(argc, argv) == EXIT_FAILURE)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
