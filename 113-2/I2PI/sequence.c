#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
    int val;
    struct _Node *next;
} Node;

void insert(Node *cur, int input, Node *head) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode -> val = input;
    newNode -> next = cur -> next;
    cur -> next = newNode;
}

void show(Node *head) {
    Node *printCur = head;
    while (printCur -> next != NULL) {
        printf("%d ", printCur -> val);
        printCur = printCur -> next;
    }
    printf("%d\n", printCur -> val);
}

Node *move(Node *cur, int steps) {
    for (int i = 0; i < steps; i++) {
        cur = cur -> next;
    }
    return cur;
}

void erase(Node *cur, int num, Node *head) {
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

    Node *head = (Node*)malloc(sizeof(Node));

    scanf("%d", &x);
    scanf("%d", &n);
    head -> val = x;
    head -> next = NULL;
    Node *cur = head;

    while (n--) {
        char command[10];
        int input, input1;
        scanf("%s", command);
        if (command[0] == 'i') {
            scanf("%d %d", &input, &input1);
            for (int i = 0; i < input1; i++) {
                insert(cur, input, head);
            }
        } else if (command[0] == 'e') {
            scanf("%d", &input);
            erase(cur, input, head);
        } else if (command[0] == 'm') {
            scanf("%d", &input);
            cur = move(cur, input);
        } else {
            show(head);
        }
    }

    return 0;
}