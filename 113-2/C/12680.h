#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include <stdio.h>
#include <stdlib.h>
typedef struct _Node{
    int size;
    int* data;
    struct _Node* next;
} Node;

Node* ReadOneList() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    int size, temp;
    scanf("%d: ", &size);
    newNode -> size = size;
    newNode -> data = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &temp);
        getchar();
        newNode -> data[i] = temp;
    }
    newNode -> next = NULL; 
    return newNode;
}

void PrintList(Node* x) {
    x = x -> next;
    while (x != NULL) {
        int size = x -> size;
        for (int i = 0; i < size - 1; i++) {
            printf("%d ", x -> data[i]);
        }
        printf("%d\n", x -> data[size - 1]);
        x = x -> next;
    }
}

void Merge(Node* x, int a, int b) {
    if (a == b) return;
    Node* prev_x = x;
    Node* temp_x = prev_x -> next;
    Node* prev_y = x;
    Node* temp_y = prev_y -> next;
    a--;
    while (a--) {
        prev_x = prev_x -> next;
        temp_x = temp_x -> next;
        if (temp_x == NULL) return;
    }
    b--;
    while (b--) {
        prev_y = prev_y -> next;
        temp_y = temp_y -> next;
        if (temp_y == NULL) return;
    }
    Node* x1 = (Node*)malloc(sizeof(Node));
    x1 -> size = temp_x -> size + temp_y -> size;
    x1 -> data = (int*)malloc(sizeof(int) * x1 -> size);
    int i;
    for (int i; i < temp_y -> size; i++) {
        x1 -> data[i] = temp_y -> data[i];
    }
    for (int j = 0; j < temp_x -> size; j++) {
        x1 -> data[i + j] = temp_x -> data[j];
    }
    if (temp_y == prev_x) {
        prev_y -> next = x1;
        x1 -> next = temp_x -> next;
    } else if (temp_x = prev_y) {
        prev_x -> next = x1;
        x1 -> next = temp_y -> next;
    } else {
        prev_y -> next = x1;
        x1 -> next = temp_y -> next;
        prev_x -> next = temp_x -> next;
    }
    free(temp_x -> data);
    free(temp_x);
    free(temp_y -> data);
    free(temp_y);
}
void Cut(Node* x, int a, int b) {
    Node* prev = (Node*)malloc(sizeof(Node));
    Node* temp = (Node*)malloc(sizeof(Node));
    a--;
    while (a--) {
        prev = prev -> next;
        temp = temp -> next;
    }
    if (temp -> size < 2) return;
    int size1 = b;
    int size2 = temp -> size - b;
    Node* x1 = (Node*)malloc(sizeof(Node));
    Node* x2 = (Node*)malloc(sizeof(Node));
    x1 -> size = size1;
    x2 -> size = size2;
    x1 -> data = (int*)malloc(sizeof(int) * size1);
    x2 -> data = (int*)malloc(sizeof(int) * size2);
    int i;
    for (i = 0; i < size1; i++) {
        x1 -> data[i] = temp -> data[i];
    }
    for (int j = 0; j < size2; j++) {
        x2 -> data[j] = temp -> data[i + j];
    }
    prev -> next = x1;
    x1 -> next = x2;
    x2 -> next = temp -> next;
    free(temp -> data);
    free(temp);
}

#endif