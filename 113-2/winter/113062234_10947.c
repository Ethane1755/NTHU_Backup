#include "function.h"

Node* createList() {
    int data;
    Node *head = NULL, *tail = NULL;

    while (scanf("%d", &data) && data != -1) {
        Node *newNode = (Node*)malloc(sizeof(Node));
        newNode->data = data;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}

void deleteNode(Node **head, int pos) {
    if (*head == NULL || pos <= 0) return;

    Node *temp = *head;

    if (pos == 1) {
        *head = temp->next;
        free(temp);
        return;
    }

    Node *prev = NULL;
    for (int i = 1; i < pos && temp != NULL; i++) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}
