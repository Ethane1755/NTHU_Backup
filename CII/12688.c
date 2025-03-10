#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    char chr;
    struct _Node* next;
    struct _Node* prev;
} Node;

void backspace(Node** nodeptr) {
    Node* CurNode = (*nodeptr);
    if (CurNode -> prev == NULL) return;
    if (CurNode -> next == NULL) {
        (*nodeptr) = CurNode -> prev;
        (*nodeptr) -> next = NULL;
        free(CurNode);
    }
    else {
        CurNode -> prev -> next = CurNode -> next;
        CurNode -> next -> prev = CurNode -> prev;
        (*nodeptr) = CurNode -> prev;
        free(CurNode);
    }
}

void insert(Node** nodeptr, char input) {
    Node* CurNode = (*nodeptr);
    Node* NewNode = (Node*)malloc(sizeof(Node));
    NewNode -> chr = input;
    NewNode -> prev = CurNode;
    NewNode -> next = CurNode -> next;

    if (CurNode -> next != NULL) {
        CurNode -> next -> prev = NewNode;
    }
    CurNode -> next = NewNode;
    (*nodeptr) = NewNode;
}

void print(Node* head) {
    Node* CurNode = head -> next;
    while (CurNode != NULL) {
        printf("%c", CurNode -> chr);
        Node* temp = CurNode;
        CurNode = CurNode -> next;
        free(temp);
    }
    free(head);
    printf("\n");
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        Node* head = (Node*)malloc(sizeof(Node));
        head -> prev = NULL;
        head -> next = NULL;
        Node* CurNode = head;
        int N;
        scanf("%d", &N);
        getchar();
        while(N--) {
            char input = getchar();
            if (input == 'L') {
                if (CurNode -> prev != NULL) {
                    CurNode = CurNode -> prev;
                }
            } else if (input == 'R') {
                if (CurNode -> next != NULL) {
                    CurNode = CurNode -> next;
                }
            } else if (input == 'B') {
                backspace(&CurNode);
            } else {
                insert(&CurNode, input);
            }
        }
        print(head);
    }
    return 0;
}