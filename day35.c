#include <stdio.h>
#include <stdlib.h>

// Node for linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Queue with front and rear pointers
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Initialize empty queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// Enqueue: insert at rear (dynamic allocation)
void enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;

    if (q->rear == NULL) {
        // Empty queue: front and rear both point to new node
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Dequeue: remove from front (free memory)
int dequeue(Queue* q) {
    if (q->front == NULL) {
        fprintf(stderr, "Queue underflow\n");
        exit(1);
    }
    Node* temp = q->front;
    int val = temp->data;
    q->front = temp->next;
    if (q->front == NULL)
        q->rear = NULL;  // Queue became empty
    free(temp);           // Dynamic memory freed
    return val;
}

// Display from front to rear
void display(Queue* q) {
    Node* curr = q->front;
    while (curr != NULL) {
        printf("%d", curr->data);
        if (curr->next != NULL) printf(" ");
        curr = curr->next;
    }
    printf("\n");
}

// Free entire queue
void freeQueue(Queue* q) {
    while (q->front != NULL) dequeue(q);
    free(q);
}

int main() {
    int n;
    scanf("%d", &n);

    Queue* q = createQueue();

    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        enqueue(q, val);
    }

    display(q);
    freeQueue(q);
    return 0;
}