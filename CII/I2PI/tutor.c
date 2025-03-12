#include <stdio.h>
#include <stdlib.h>

// Define the node structure at the top of the file
struct Node {
    int data;
    struct Node* next;  // Pointer to the next node
};

// Create a linked list with n nodes
struct Node* createList(int n) {
    struct Node* head = NULL;
    struct Node* temp = NULL;
    struct Node* current = NULL;

    // Create a list with values 1 to n
    for (int i = 1; i <= n; i++) {
        temp = (struct Node*)malloc(sizeof(struct Node));  // Allocate memory for a new node
        temp->data = i;
        temp->next = NULL;

        if (head == NULL) {
            head = temp;
            current = head;
        } else {
            current->next = temp;
            current = temp;
        }
    }
    current->next = head;  // Make it a circular linked list (pointing last node to head)
    return head;
}

// Solve the Josephus problem using modulo for circular traversal
int solveJosephus(struct Node** head, int k) {
    struct Node* temp = *head;
    struct Node* prev = NULL;
    int n = 0;

    // Count the number of nodes in the circular list
    do {
        n++;
        temp = temp->next;
    } while (temp != *head);

    temp = *head;

    // Loop until only one node remains
    while (n > 1) {
        // Find the (k-1)th node (because we count from 1, not 0)
        for (int i = 1; i < k; i++) {
            prev = temp;
            temp = temp->next;
        }

        // Eliminate the k-th node (temp)
        prev->next = temp->next;  // Remove the k-th node
        free(temp);                // Free memory
        temp = prev->next;         // Move to the next node
        n--;                       // Decrease the count of nodes
    }

    // Return the last remaining node's data
    int result = temp->data;
    free(temp);  // Free the last node
    return result;
}

// Free the list
void freeList(struct Node* head) {
    if (head == NULL) return;
    struct Node* temp = head;
    while (temp->next != head) {
        struct Node* toDelete = temp;
        temp = temp->next;
        free(toDelete);
    }
    free(temp);  // Free the last node
}

int main() {
    int n, k;
    while (scanf("%d %d", &n, &k) != EOF) {
        struct Node* head = createList(n);  // Create the linked list
        printf("%d\n", solveJosephus(&head, k));  // Solve and print the result
        freeList(head);  // Free the linked list
    }
    return 0;
}