#include "10966.h"
#include <stdlib.h>
#include <stdio.h>

BTNode* makeNode(char c) {
    BTNode* NewNode = (BTNode*)malloc(sizeof(BTNode));

    switch (c){
        case 'A':
            NewNode -> data = ID_A;
            NewNode -> left = NULL;
            NewNode -> right = NULL;
            break;
        case 'B':
            NewNode -> data = ID_B;
            NewNode -> left = NULL;
            NewNode -> right = NULL;
            break;
        case 'C':
            NewNode -> data = ID_C;
            NewNode -> left = NULL;
            NewNode -> right = NULL;
            break;
        case 'D':
            NewNode -> data = ID_D;
            NewNode -> left = NULL;
            NewNode -> right = NULL;
            break;
        case '|':
            NewNode -> data = OP_OR;
            break;
        case '&':
            NewNode -> data = OP_AND;
            break;
    }
    
    return NewNode;
}  

BTNode* EXPR()  {
    BTNode *right = NULL, * root = NULL;
    if (pos >= 0) {
        char c = expr[pos--];
        if (c >= 'A' && c <= 'D') {
            right = makenode(c);
        } else if (c == ')') {
            right = EXPR();
            pos--;
        } 
        if (pos > 0) {
            c = expr[pos];
            if (c == '|' || c == '&') {
                root = makeNode(c);
                root -> right = right;
                pos--;
                root -> left = EXPR();
            }
            else root = right;
        }
        else root = right;     
    }
    return root;
}


