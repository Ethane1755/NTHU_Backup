#include <stdio.h>

typedef struct  _node {
    int id;
    struct _node* true;
    struct _node* false;
} Node;

Node hole[3005];
Node* root;
int pos = 0;
char expr[3005];

Node* makeNode (int id) {
    Node* newNode = &hole[pos++];
    newNode -> id = id;
    newNode -> false = NULL;
    newNode -> true = NULL;
    return newNode;
}

Node* createTree() {
    int id;
    scanf("%d", &id);
    char op;
    scanf("%c", &op);
    Node* newNode = makeNode(id);

    if (op == '?') {
        newNode -> true = createTree();
        newNode -> false = createTree();
    }

    return newNode;
}

int count (Node* root) {
    if (root -> true && root -> false) {
        return expr[root -> id] - '0' ? count (root -> true) : count(root -> false);
    }
    return expr[root -> id] - '0';
}

int main () {
    int T;
    root = createTree();
    scanf("%d", &T);
    while (T--) {
        scanf("%s", expr + 1);
        printf("%d\n", count(root));
    }
}