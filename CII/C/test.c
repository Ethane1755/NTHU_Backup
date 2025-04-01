#include <stdio.h>

typedef struct _node {
    int id;
    struct _node* true, * false;
} Node;

Node* Root;
Node hole[3005]; // substitute malloc
int len = 0, pos = 0;
char expr[3005];

Node* make_node(int data);
Node* create_tree();
int count(Node* root);

int main() {
    int T;
    Root = create_tree();
    scanf("%d", &T);
    while (T--) {
        scanf("%s", expr + 1);
        printf("%d\n", count(Root));
    }
}

Node* make_node(int id) {
    Node* new_node = &hole[pos++];
    new_node->id = id;
    new_node->true = NULL;
    new_node->false = NULL;
    return new_node;
}

Node* create_tree() {

    // get the id
    int id;
    scanf("%d", &id);
    if (id > len) len = id;

    // every id is followed by an op
    char op;
    scanf("%c", &op);

    // create node
    Node* new_node = make_node(id);

    // op maybe '?', ':', '\n'
    if (op == '?') {
        new_node->true = create_tree();
        new_node->false = create_tree();
    }

    return new_node;
}

int count(Node* root) {
    if (root->true && root->false)
        return expr[root->id] - '0' ? count(root->true) : count(root->false);

    return expr[root->id] - '0';
}

// Utin
