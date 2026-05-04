// Day 42: Reverse a Queue using a Stack
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// ---- Queue Implementation ----
typedef struct {
    int arr[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isQueueEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, int val) {
    if (q->front == -1)
        q->front = 0;
    q->arr[++q->rear] = val;
}

int dequeue(Queue *q) {
    int val = q->arr[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return val;
}

// ---- Stack Implementation ----
typedef struct {
    int arr[MAX];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isStackEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int val) {
    s->arr[++s->top] = val;
}

int pop(Stack *s) {
    return s->arr[s->top--];
}

// ---- Reverse Queue using Stack ----
void reverseQueue(Queue *q) {
    Stack s;
    initStack(&s);

    // Step 1: Dequeue all elements and push onto stack
    while (!isQueueEmpty(q)) {
        push(&s, dequeue(q));
    }

    // Step 2: Pop all elements from stack and enqueue back
    while (!isStackEmpty(&s)) {
        enqueue(q, pop(&s));
    }
}

int main() {
    Queue q;
    initQueue(&q);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        enqueue(&q, val);
    }

    reverseQueue(&q);

    // Print the reversed queue
    while (!isQueueEmpty(&q)) {
        printf("%d ", dequeue(&q));
    }
    printf("\n");

    return 0;
}
