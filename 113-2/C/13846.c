#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int data;
    struct _node* less;
    struct _node* more;
} Node;

Node* makeNode (int input) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode -> data = input;
    newNode -> less = newNode -> more = NULL;
    return newNode;
}

void makeTree(Node* root, int temp) {
    if (temp <= root -> data) {
        if (root -> less) makeTree(root -> less, temp); 
        else root -> less = makeNode(temp);
    } else {
        if (root -> more) makeTree(root -> more, temp);
        else root -> more = makeNode(temp);
    }
}

void printTree(Node* root, int tail) {
    if (root -> less) printTree(root -> less, 0);
    if (root -> more) printTree(root -> more, 0);
    printf("%d", root -> data); 
    tail ? printf("\n") : printf(" ");
}

int main () {
    int N, a0, a;
    scanf("%d", &N);
    N--;
    scanf("%d", &a0);
    Node* root = makeNode(a0);
    
    while (N--) {
        scanf("%d", &a);
        makeTree(root, a);
    }
    printTree(root, 1);
    return 0;
}

