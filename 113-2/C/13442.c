#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    int number, age;
    struct _Node* prev;
    struct _Node* next;
}Node;

Node* head;
Node* order[5000001];

int cmp(const void* a, const void* b) {
    Node* A = *(Node**) a;
    Node* B = *(Node**) b;
    if (A->age != B->age) return A->age - B->age;
    else return A->number - B->number;
}

Node* createList(int n){
    Node* NewNode = (Node*)malloc(sizeof(Node) * n);
    for (int i = 0; i < n; i++) {
        scanf(" %d", &NewNode[i].age);
        NewNode[i].number = i + 1;
        order[i] = &NewNode[i];
        if (i == 0) NewNode[i].prev = &NewNode[n - 1];
        else NewNode[i].prev = &NewNode[i - 1];
        if (i == n - 1) NewNode[i].next = &NewNode[0];
        else NewNode[i].next = &NewNode[i + 1];
    }
    qsort(order, n, sizeof(Node*), cmp);
    return NewNode;
}
Node* solve(int n, int m) {
    int a, b;
    char c;
    while(m--){
        scanf("%d %d %c", &a, &b, &c);
        a--;
        b %= (n - 1);
        if (b == 0) continue;

        Node* cur = order[a];
        Node* next = order[a]->next;
        Node* pre = order[a]->prev;
        next -> prev = pre;
        pre -> next = next;

        if (c == 'R') {
            while(b--) {
                pre = pre -> next;
                next = next -> next;
            }
        } else {
            while(b--){
                pre = pre -> prev;
                next = next -> prev;
            }
        }
        pre -> next = cur;
        next -> prev = cur;
        cur -> next = next;
        cur -> prev = pre;
    }
    return order[0];
}

#endif