typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef Node *PNode;

void print_nodes(PNode Head, char *name);

void add_node(PNode *Head, PNode NewNode);

PNode create_node(int value);

PNode find_value(int value, PNode Head);

PNode find_before_value(int value, PNode Head);

void delete_node_by_value(int value, PNode *Head);

void delete_node(PNode *Head, PNode OldNode);

void delete_max_value(PNode *Head);

void change_node_value(int new_value, PNode *Node, PNode *Head);

PNode read_file_nodes(char *file_name);
