#ifndef _FUNCTION_H_
#define _FUNCTION_H_

typedef struct Node {
    int val;
    struct Node *next;
} Node;

Node *getCycleEnd(Node *head);
Node *deleteNode(Node *head);

// You might start with the following codes:

/*
#include <stdio.h>
#include <stdlib.h>
#include "function.h"

Node *getCycleEnd(Node *head) {
    // ...
}

Node *deleteNode(Node *head) {
    // ...
}
*/

#endif