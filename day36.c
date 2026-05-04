#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* front = NULL;
struct node* rear = NULL;

void enqueue(int val) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = val;
    newNode->next = NULL;
    if (rear == NULL) {
        front = rear = newNode;
        rear->next = front; // circular
        return;
    }
    rear->next = newNode;
    rear = newNode;
    rear->next = front; // maintain circular
}

void dequeue() {
    if (front == NULL) { printf("Empty!\n"); return; }
    if (front == rear) { // single element
        free(front);
        front = rear = NULL;
        return;
    }
    struct node* temp = front;
    front = front->next;
    rear->next = front; // maintain circular
    free(temp);
}

void display() {
    if (front == NULL) { printf("Empty!\n"); return; }
    struct node* temp = front;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != front);
    printf("\n");
}

int main() {
    int n, m, val;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        enqueue(val);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
        dequeue();
    display();
    return 0;
}
