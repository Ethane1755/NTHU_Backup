#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BTNode {
    int c;
    struct BTNode* left;
    struct BTNode* right;
}BTNode;

BTNode* createNode (int input) {
    BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
    switch (input) {
        case 'A' :
            newNode -> c = input;
            newNode -> left = newNode -> right = NULL;
            break;
        case 'B' :
            newNode -> c = input;
            newNode -> left = newNode -> right = NULL;
            break;
        case 'C' :
            newNode -> c = input;
            newNode -> left = newNode -> right = NULL;
            break;
        case 'D' :
            newNode -> c = input;
            newNode -> left = newNode -> right = NULL;
            break;
        case '|' :
            newNode -> c = input;
            break;
        case '&' :
            newNode -> c = input;
            break;
    }
    return newNode;
}

BTNode* parser () {
    char c = getchar();
    BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
    if (c == '&' || c == '|') {
        newNode = createNode(c);
        newNode -> c = c;
        newNode -> left = parser();
        newNode -> right = parser();
    } else {
        newNode = createNode(c);
    }
    return newNode;
}

int eval(BTNode* root, int A, int B, int C, int D) {
    int inp = root -> c;
    if (inp == 'A') inp = A;
    else if (inp == 'B') inp = B;
    else if (inp == 'C') inp = C;
    else if (inp == 'D') inp = D;
    if (inp == '|' || inp == '&') {
        int op1 = eval(root -> left, A, B, C, D);
        int op2 = eval(root -> right, A, B, C, D);
        if (inp == '|') return (op1 | op2);
        else return (op1 & op2);
    } else {
        return inp;
    }
}

void freeTree(BTNode* root) {
    if (!root) return;
    free(root -> left);
    free(root -> right);
    free(root);
}

int main () {
    int c;
    BTNode* root = (BTNode*)malloc(sizeof(BTNode));
    root = parser();
    //preorder(root);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 2; l++) {
                    int ans = eval(root, i, j, k, l);
                    printf("%d %d %d %d %d\n", i, j, k, l, ans);
                }
            }
        }
    }
    freeTree(root);
    return 0;
}