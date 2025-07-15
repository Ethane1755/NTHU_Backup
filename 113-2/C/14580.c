#include <stdio.h>
#include <stdlib.h>
#include "14580.h"

// Floyd's Tortoise and Hare to find cycle end
Node *getCycleEnd(Node *head) {
    if (!head) return NULL;
    Node *slow = head, *fast = head;
    // Detect cycle
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    if (!fast || !fast->next) return NULL; // No cycle

    // Find start of cycle
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    Node *cycleStart = slow;

    // Find end of cycle
    Node *ptr = cycleStart;
    while (ptr->next != cycleStart) {
        ptr = ptr->next;
    }
    return ptr;
}

Node *deleteNode(Node *head) {
    int T;
    scanf("%d", &T);

    while (T--) {
        int A;
        scanf("%d", &A);
        Node *prev = NULL, *cur = head;
        Node *cycleEnd = getCycleEnd(head);
        Node *cycleStart = NULL;
        if (cycleEnd) cycleStart = cycleEnd->next;

        // To avoid infinite loop in cycle, stop at cycleEnd if exists
        while (cur) {
            if (cur->val == A) {
                if (prev == NULL) { // delete head
                    if (cycleEnd && cur == head) {
                        if (head->next == head) { // self-loop
                            head = NULL;
                        } else {
                            cycleEnd->next = head->next;
                            head = head->next;
                        }
                    } else {
                        head = head->next;
                    }
                } else {
                    prev->next = cur->next;
                    if (cycleEnd && cur == cycleStart) {
                        cycleEnd->next = cur->next;
                    }
                }
                break;
            }
            if (cycleEnd && cur == cycleEnd) break;
            prev = cur;
            cur = cur->next;
        }
    }
    return head;
}

void printLinkedList(Node *head) {
    if(head == NULL){
        printf("EMPTY!!!\n");
        return ;
    }
    Node *End = getCycleEnd(head);
    Node *cur = head;
    while(cur->next != NULL && cur != End){
        printf("%d ", cur->val);
        cur = cur->next;
    }
    printf("%d\n", cur->val);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *val = (int*)malloc(sizeof(int) * (n + 1));
    for(int i=1; i <= n; i++) scanf("%d", &val[i]);

    Node **nodes = (Node**)malloc(sizeof(Node*) * (n + 1));
    for(int i=1; i <= n; i++) nodes[i] = (Node*)malloc(sizeof(Node));
    for(int i=1; i <= n; i++) {
        nodes[i]->val = val[i];
        if(i != n) nodes[i]->next = nodes[i+1];
        else nodes[i]->next = NULL;
    }
    if(m != 0) nodes[n]->next = nodes[m];

    printLinkedList(deleteNode(&(*nodes[1])));

    for(int i=1; i <= n; i++) free(nodes[i]);
    free(nodes);
    free(val);

    return 0;
}