#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_WORD_LENGTH 80
#define COUNT 2

typedef struct Node {
    char *word; // слово строки
    int pos; // номер позиции строки, с которого начинается слово
    struct Node *right;
    struct Node *left;
} Node;

typedef Node *PNode;

PNode create_node(char *word, int pos) {
    PNode NewNode = (PNode)malloc(sizeof(Node));
    NewNode->word = word;
    NewNode->pos = pos;
    NewNode->left = NULL;
    NewNode->right = NULL;

    return NewNode;
}

void insert(PNode *Root, char *word, int pos) {
    if (*Root == NULL) {
        *Root = create_node(word, pos);
        return;
    }

    if (word[0] >= ((*Root)->word)[0])
        insert(&((*Root)->right), word, pos);
    else
        insert(&((*Root)->left), word, pos);
}

PNode read_file_nodes(char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("\nТакого файла не существует!\n");
        exit(1);
    }

    PNode Root = NULL;
    int pos = 1, ch = fgetc(file), j;

    while (1) {
        while (ch == ' ' || ch == '\n') {
            ch = fgetc(file);
            if (ch == EOF)
                return Root;

            pos++;
        }

        char *word = (char *)malloc(MAX_WORD_LENGTH * sizeof(char));
        for (j = 0; ch != ' ' && ch != '\n'; j++) {
            word[j] = (char)ch;

            ch = fgetc(file);
            if (ch == EOF) {
                word[j + 1] = '\0';
                insert(&Root, word, pos);
                return Root;
            }
        }
        word[j] = '\0';

        insert(&Root, word, pos);
        pos += j;
    }

    fclose(file);
}

int search_word(PNode Root, char *word) {
    PNode TempNode = Root;
    while (TempNode) {
        if (strcmp(TempNode->word, word) == 0)
            return TempNode->pos;
        else if (word[0] < (TempNode->word)[0])
            TempNode = TempNode->left;
        else
            TempNode = TempNode->right;
    }

    return -1;
}

int run(int argc, char *argv[]) {
    char file_name[MAX_FILENAME_LENGTH];
    printf("Введите название файла: ");
    scanf("%255s", file_name); // \0 в конце
    while (getchar() != '\n')  // Очищаем буффер
        ;

    PNode Root = read_file_nodes(file_name);

    char word[MAX_WORD_LENGTH];
    printf("Введите слово для поиска: ");
    scanf("%79s", word); // \0 в конце
    while (getchar() != '\n')  // Очищаем буффер
        ;

    int pos = search_word(Root, word);
    printf("Позиция слова: %d\n", pos);

    PNode TempNode = Root;
    while (TempNode) {
        printf("%s\n", TempNode->word);
        TempNode = TempNode->left;
    }

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
