/* Вариант 7
 * Рандомизованная вставка элемента в BST-дерево, балансировка дерева. */

#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FILENAME_LENGTH 256

static char integers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
/*converts long to a string representation and returns it:*/
char *long2str(char *buf, long n) {
    char tmp[22]; /* This is a stack.
                    64/Log_2[10] = 19.3, so this is enough forever...*/
    unsigned long u;
    char *bufptr = buf, *tmpptr = tmp + 1;

    if (n < 0) { /*Swap the sign and store '-':*/
        /*INT_MIN workaround:*/
        u = ((unsigned long)(-(1 + n))) + 1;
        *bufptr++ = '-';
    } else
        u = n;

    *tmp = '\0'; /*terminator*/

    /*Fill up the stack:*/
    do
        *tmpptr++ = integers[u % 10];
    while (u /= 10);

    /*Copy the stack to the output buffer:*/
    while ((*bufptr++ = *--tmpptr) != '\0')
        ;
    return buf;
}

typedef struct Node {
    int value;
    int amount;
    struct Node *right;
    struct Node *left;
} Node;

typedef Node *PNode;

PNode create_node(int value, int amount) {
    PNode NewNode = (PNode)malloc(sizeof(Node));
    NewNode->value = value;
    NewNode->amount = amount;
    NewNode->left = NULL;
    NewNode->right = NULL;

    return NewNode;
}

void print_nodes(PNode Root, int n, int a, int b) {
    if (Root != NULL) {
        char *buf = (char *)malloc(sizeof(char) * 100);
        mvaddstr(n, (a + b) / 2, long2str(buf, Root->value));
        free(buf);
        print_nodes(Root->right, n + 3, (a + b) / 2, b);
        print_nodes(Root->left, n + 3, a, (a + b) / 2);
    }
}

void rotate_left(PNode *Root) {
    if ((*Root)->right == NULL)
        return;

    PNode Node = (*Root)->right;
    int k = (*Root)->amount;
    (*Root)->right = Node->left;
    Node->left = (*Root);
    (*Root) = Node;
    (*Root)->amount = k;
    (*Root)->left->amount = 1;
    if ((*Root)->left->right != NULL)
        (*Root)->left->amount += ((*Root)->left->right->amount);
    if ((*Root)->left->left != NULL)
        (*Root)->left->amount += ((*Root)->left->left->amount);
}

void rotate_right(PNode *Root) {
    if ((*Root)->left == NULL)
        return;

    PNode Node = (*Root)->left;
    int k = (*Root)->amount;
    (*Root)->left = Node->right;
    Node->right = (*Root);
    (*Root) = Node;
    (*Root)->amount = k;
    (*Root)->right->amount = 1;
    if ((*Root)->right->right != NULL)
        (*Root)->right->amount += ((*Root)->right->right->amount);
    if ((*Root)->right->left != NULL)
        (*Root)->right->amount += ((*Root)->right->left->amount);
}

void insert_root(PNode *Root, int value) {
    if (*Root == NULL) {
        *Root = create_node(value, 1);
        return;
    }
    ((*Root)->amount)++;

    if (value > (*Root)->value) {
        insert_root(&((*Root)->right), value);
        rotate_left(Root);
    } else if (value == (*Root)->value)
        insert_root(&((*Root)->right), value);
    else {
        insert_root(&((*Root)->left), value);
        rotate_right(Root);
    }
}

void insert(PNode *Root, int value) {
    if (*Root == NULL) {
        *Root = create_node(value, 1);
        return;
    }

    float z = (float)((float)(rand() % 9999 + 1) / 10000);

    // char *buf = (char *)malloc(sizeof(char) * 100);
    // clear();
    // mvaddstr(0, 0, "Adding elements to a tree: ");
    // print_nodes(*Root, 0, 0, 125);
    // mvaddstr(1, 0, "0.");
    // mvaddstr(1, 2, long2str(buf, (long)(z * 1000)));
    // mvaddstr(1, 7, "< 0.");
    // mvaddstr(
    //     1, 11,
    //     long2str(buf, (long)(((float)1) / ((*Root)->amount + 1.0) * 1000)));
    // refresh();
    // getch();
    // free(buf);

    if (z < (1.0 / ((*Root)->amount + 1.0))) {
        insert_root(Root, value);
        return;
    }

    if (value < (*Root)->value)
        insert(&((*Root)->left), value);
    else
        insert(&((*Root)->right), value);
    ((*Root)->amount)++;
}

PNode create_random_bst(int amount) {
    PNode Root = NULL;

    for (int i = 0; i < amount; i++) {
        clear();
        mvaddstr(0, 0, "Adding elements to a tree: ");
        // insert(&Root, rand() % 90 + 10);
        mvaddstr(2, 0, "Added element");
        insert(&Root, i);
        print_nodes(Root, 0, 0, 125);
        refresh();
        getch();
    }
    clear();

    return Root;
}

void partition(PNode *Root, int k) {
    if ((*Root) == NULL)
        return;

    int T = ((*Root)->left == NULL) ? 0 : (*Root)->left->amount;

    if (T > k) {
        partition(&((*Root)->left), k);
        rotate_right(Root);
    }
    if (T < k) {
        partition(&((*Root)->right), k - T - 1);
        rotate_left(Root);
    }
}

void balance(PNode *Root) {
    if ((*Root) == NULL || (*Root)->amount == 1)
        return;
    partition(Root, ((*Root)->amount) / 2);

    // clear();
    // mvaddstr(0, 0, "Balancing: ");
    // print_nodes(*Root, 0, 0, 125);
    // refresh();
    // getch();

    balance(&((*Root)->left));
    balance(&((*Root)->right));
}

int run(int argc, char *argv[]) {
    int amount;
    printf("Введите количество элементов: ");
    scanf("%d", &amount);
    while (getchar() != '\n')
        ;

    initscr();
    cbreak();
    noecho();
    PNode Root = create_random_bst(amount);
    print_nodes(Root, 0, 0, 125);
    mvaddstr(0, 0, "Adding elements to a tree: END");
    refresh();
    getch();

    clear();
    balance(&Root);
    mvaddstr(0, 0, "Balancing: END");
    print_nodes(Root, 0, 0, 125);
    refresh();
    getch();

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
#ifdef _WIN32
    system("chcp 65001");
#endif

    srand(time(NULL));

    if (run(argc, argv) == EXIT_FAILURE)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
