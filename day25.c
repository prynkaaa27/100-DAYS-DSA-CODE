#include <stdio.h>
#include <stdlib.h>

// Definition of Linked List Node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to count occurrences of key
int countOccurrences(struct Node* head, int key) {
    int count = 0;
    struct Node* temp = head;

    while (temp != NULL) {
        if (temp->data == key) {
            count++;
        }
        temp = temp->next;
    }

    return count;
}

int main() {
    int n, value, key;

    // Read number of nodes
    scanf("%d", &n);

    struct Node* head = NULL;
    struct Node* tail = NULL;

    // Read elements and create linked list
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);

        struct Node* newNode = createNode(value);

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Read key
    scanf("%d", &key);

    // Count occurrences
    int result = countOccurrences(head, key);

    // Print result
    printf("%d", result);

    return 0;
}