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
    scanf("%d", &size);
    newNode -> size = size;
    for (int i = 0; i < size; i++) {
        scanf("%d", &temp);
        newNode -> data[i] = temp;
    }
    newNode -> next = NULL; 
    return newNode;
}
void PrintList(Node* x) {
    int size = x -> size;
    for (int i = 0; i < size - 1; i++) {
        printf("%d ", x -> data[i]);
    }
    printf("%d\n", x -> data[size - 1]);
    x = x -> next;
}
void Merge(Node* x, int a, int b) {
    Node* x1 = (Node*)malloc(sizeof(Node));
    Node* merged = (Node*)malloc(sizeof(Node));
    Node* forMerge = (Node*)malloc(sizeof(Node));
    Node* prev = (Node*)malloc(sizeof(Node));
    int* temp;
    x1 = x;
    while (a--) {
        x = x -> next;
    }
    forMerge = x;
    while (b >= 1) {
        x1 = x1 -> next;
        prev = x1;
    }
    x1 = x1 -> next;
    merged = x1;
    for (int i = 0; i < forMerge -> size; i++) {
        temp[i] = (forMerge -> data)[i];
    }
    for (int i = merged -> size; i < (merged -> size + forMerge -> size); i++) {
        merged -> data[i] = temp[i];
    }
    merged -> size += forMerge -> size;
    if (forMerge -> next != NULL) prev -> next = forMerge -> next;
    else prev -> next = NULL;
    free(forMerge);
}
void Cut(Node* x, int a, int b) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    int* temp;
    while (a--) {
        x = x -> next;
    }
    for (int i = b - 1; i < x -> size; i++) {
        temp[i] = x -> data[i];
    }
    newNode -> size = (x -> size) - b;
    for (int i = b - 1; i < x -> size; i++) {
        newNode -> data[i] = temp[i];
    }
    if(x -> next != NULL) newNode -> next = x -> next;
    else newNode -> next = NULL;
    x -> next = newNode;
    x -> size = b;
}

#endif