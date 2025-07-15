#include <stdio.h>
#include <stdlib.h>
#include "14582.h"

Node *root;
char str[1000010];

int main() {
    int n, t, a;
    scanf("%d\n%s", &n, str);
    root = parenthesesTree(root, str);

    scanf("%d", &t);
    while(t--){
        scanf("%d", &a);
        insert(&root, a);
    }
    
    print(root);
    printf("\n");
    
    return 0;
}

Node *parenthesesTree(Node *node, char *str) {
    if (!str || *str == '\0') return NULL; 
    Node* newNode = (Node*)malloc(sizeof(Node));
    printf("%c", *str);
    return newNode;
}
void insert(Node **node, int a) {
    if (*node == NULL) {  
        *node = (Node *)malloc(sizeof(Node));
        (*node)->val = a;
        (*node)->left = (*node)->right = NULL;
        return;
    }
    
    if (a < (*node)->val) {
        insert(&((*node)->left), a);
    } else if (a > (*node)->val) {
        insert(&((*node)->right), a);
    }
}
void print(Node *node) {
    printf("%d(", node -> val);
    if (node -> left) print(node -> left);
    else printf("()");
    if (node -> right) print(node -> right);
    else printf("()");
}