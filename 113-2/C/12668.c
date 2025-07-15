#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    char content;
    struct _Node* prev;
    struct _Node* next;
}Node;

void delete(Node** ptr) {
    Node* current = (*ptr);
    if (current->prev == NULL) return; 

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    current->prev->next = current->next;

    Node* temp = current->prev;
    free(current);
    *ptr = temp;
}

void print(Node* head) {
    Node* cur = head->next;
    while (cur!= NULL) {
        printf("%c", cur->content);
        Node* temp = cur;
        cur = cur->next;
        free(temp);
    }
    printf("\n");
    free(head);
}

void insert(Node** ptr, char input) {
    Node* current = (*ptr);
    Node* NewNode = (Node*)malloc(sizeof(Node));
    NewNode->content = input;
    NewNode->next = current->next;
    NewNode->prev = current;
    if (current->next != NULL) {
        current->next->prev = NewNode;
    }
    current->next = NewNode;
    (*ptr) = NewNode;
}


int main() {
    int T, N;
    scanf("%d", &T);
    while(T--) {
        Node* head = (Node*)malloc(sizeof(Node));
        head->prev = NULL;
        head->next = NULL;
        Node* ptr = head;
        scanf("%d", &N);
        getchar();
        while(N--) {
            char input;
            scanf(" %c", &input);
            if (input == 'R') {
                if (ptr->next != NULL) {
                    ptr = ptr->next;
                }
            } else if (input == 'L') {
                if (ptr->prev != NULL) {
                    ptr = ptr->prev;
                }
            } else if (input == 'B') {
                delete(&ptr);
            } else {
                insert(&ptr, input);
            }
        }
       print(head);
    }
    return 0;
}