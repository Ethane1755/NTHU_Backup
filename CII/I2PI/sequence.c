#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
    int val;
    struct _Node *next;
} Node;

Node *np;
Node *head;

void insert(Node *cur, int input) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode -> val = input;
    newNode -> next = head;
    cur -> next = newNode;
}

void show() {
    Node *printCur = head;
    while (printCur -> next != NULL) {
        printf("%d ", printCur -> val);
        printCur = printCur -> next;
    }
    printf("%d\n", printCur -> val);
}

void move(Node *cur, int steps) {
    for (int i = 0; i < steps; i++) {
        cur = cur -> next;
    }
}

void erase(Node *cur, int num) {
    Node *move = cur;
    int flag = 0;
    for (int i = 0; i < num; i++) {
        move = move -> next;
        if (move == head) flag = 1;
    }
    cur -> next = move;
    if(flag) head = move;
}

int main () {
    int x, n;
    head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    np = head;

    scanf("%d", &x);
    scanf("%d", &n);
    insert(np, x);
    Node *cur = head->next;

    while (n--) {
        char command[10];
        int input, input1;
        scanf("%s", command);
        if (command[0] == 'i') {
            scanf("%d %d", &input, &input1);
            for (int i = 0; i < input1; i++) {
                insert(cur, input);
            }   
        } else if (command[0] == 'e') {
            scanf("%d", &input);
            erase(cur, input);
        } else if (command[0] == 'm') {
            scanf("%d", &input);
            move(cur, input);
        } else {
            show();
        }
    }

    return 0;
}