#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    char data;
    struct _node* left;
    struct _node* right;
} Node;

Node hole[11];
Node* head;
int pos = 0;
int n, m, q;

Node* newOperator(int input) {
    Node* newNode = &hole[pos++];
    scanf("%c", &newNode -> data);

}

Node* makeNode(int input) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode -> data = input;
    newNode -> left = newNode -> right = NULL;
    return newNode;
}

Node* createTree() {
    char temp;
    scanf(" %c", &temp);
    if (temp == '+' || temp == '-' || temp == '*') {
        head = makeNode(temp);
        head -> left = createTree();
        head -> right = createTree();
    } else {
        head = makeNode(temp);
    }
    return head;
}


int main () {
    int question;
    scanf("%d %d %d", &n, &m, &q);
    while (m--) {

    }
    Node* head = (Node*)malloc(sizeof(Node));
    n--;
    while (n--) {
        createTree(head);
    }
    while (q--) {
        scanf("%d", &question);
        if (question == 1) {

        } else if (question == 2) {

        } else if (question == 3) {

        } else if (question == 4) {
            
        }
    }
    return 0;
}