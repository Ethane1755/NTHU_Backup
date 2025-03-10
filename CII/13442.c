#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node{
    int number, age;
    struct _Node* prev;
    struct _Node* next;
} Node;

Node* head;
Node* age_list[5000001];

int cmp(const void* a, const void* b) {
    Node* A = *(Node**) a;
    Node* B = *(Node**) b;
    if (A->age != B->age) return A->age - B->age;
    else return A->number - B->number;
}

Node* createList(int n) {
    Node* list = (Node*) malloc(sizeof(Node) * n);

    for (int i = 0; i < n; i++) {
        list[i].number = i + 1;
        scanf("%d", &list[i].age);

        // record the Node*
        age_list[i] = &list[i];

        // connect the circular linked list
        if (i != n-1) list[i].next = &list[i+1];
        else list[i].next = &list[0];
        if (i != 0) list[i].prev = &list[i-1];
        else list[i].prev = &list[n-1];
    }

    // sort the Node* array
    qsort(age_list, n, sizeof(Node*), cmp);

    return list;
}

Node* solve(int n, int m) {
	int a, k;
	char dir;
	while (m--) {
        scanf("%d %d %c", &a, &k, &dir);
        a--;
        k %= (n-1);
        if (k == 0) continue;

        // take the target node out of the linked list
        Node* flag = age_list[a];
        Node* next = age_list[a]->next;
        Node* pre = age_list[a]->prev;
        pre->next = next;
        next->prev = pre;

        // search the position
        if (dir == 'R') {
            while (k--) {
                pre = pre->next;
                next = next->next;
            }
        }
        else {
            while (k--) {
                pre = pre->prev;
                next = next->prev;
            }
        }

        // insert the node back to the linked list
        pre->next = flag;
        flag->prev = pre;
        flag->next = next;
        next->prev = flag;
    }

    return age_list[0];
}

#endif

// By Utin
