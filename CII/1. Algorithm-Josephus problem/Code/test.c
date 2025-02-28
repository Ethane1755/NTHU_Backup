#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function prototypes
Node* createNode(int value);
void insertAtBeginning(Node** head, int value);
void insertAtEnd(Node** head, int value);
void insertAfter(Node* prevNode, int value);
void deleteNode(Node** head, int value);
void printList(Node* head);
int searchNode(Node* head, int value);
int getLength(Node* head);
void freeList(Node** head);

int main() {
    Node* head = NULL;  // Initialize empty list
    
    // Test insertAtBeginning
    printf("\n1. Testing insertAtBeginning:\n");
    insertAtBeginning(&head, 10);
    insertAtBeginning(&head, 20);
    insertAtBeginning(&head, 30);
    printList(head);    // Expected: 30 -> 20 -> 10
    
    // Test insertAtEnd
    printf("\n2. Testing insertAtEnd:\n");
    insertAtEnd(&head, 40);
    insertAtEnd(&head, 50);
    printList(head);    // Expected: 30 -> 20 -> 10 -> 40 -> 50
    
    // Test insertAfter
    printf("\n3. Testing insertAfter:\n");
    insertAfter(head->next, 25);  // Insert after second node
    printList(head);    // Expected: 30 -> 20 -> 25 -> 10 -> 40 -> 50
    
    // Test search
    printf("\n4. Testing search:\n");
    int searchValue = 25;
    printf("Searching for %d: %s\n", searchValue, 
           searchNode(head, searchValue) ? "Found" : "Not Found");
    
    // Test length
    printf("\n5. Testing length:\n");
    printf("Length of list: %d\n", getLength(head));
    
    // Test deletion
    printf("\n6. Testing deletion:\n");
    deleteNode(&head, 25);
    printf("After deleting 25:\n");
    printList(head);
    deleteNode(&head, 30);
    printf("After deleting 30:\n");
    printList(head);
    
    // Free the list
    freeList(&head);
    return 0;
}

// Create a new node
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Insert at the beginning
void insertAtBeginning(Node** head, int value) {
    Node* newNode = createNode(value);
    newNode->next = *head;
    *head = newNode;
}

// Insert at the end
void insertAtEnd(Node** head, int value) {
    Node* newNode = createNode(value);
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Insert after a given node
void insertAfter(Node* prevNode, int value) {
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL\n");
        return;
    }
    
    Node* newNode = createNode(value);
    newNode->next = prevNode->next;
    prevNode->next = newNode;
}

// Delete a node with given value
void deleteNode(Node** head, int value) {
    if (*head == NULL) return;
    
    Node* temp = *head;
    Node* prev = NULL;
    
    // If head node itself holds the value
    if (temp != NULL && temp->data == value) {
        *head = temp->next;
        free(temp);
        return;
    }
    
    // Search for the value
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }
    
    // If value not present
    if (temp == NULL) return;
    
    // Unlink the node
    prev->next = temp->next;
    free(temp);
}

// Print the linked list
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Search for a value
int searchNode(Node* head, int value) {
    Node* current = head;
    while (current != NULL) {
        if (current->data == value)
            return 1;
        current = current->next;
    }
    return 0;
}

// Get length of the list
int getLength(Node* head) {
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Free the entire list
void freeList(Node** head) {
    Node* current = *head;
    Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    *head = NULL;
}