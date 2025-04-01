#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;

typedef struct Node {
    int val;
    struct Node *left;
    struct Node *right;
} Node;

Node *parenthesesTree(Node *node, char *str);
void insert(Node **node, int a);
void print(Node* node);

#endif