// Day 46: Level Order Traversal of a Binary Tree
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// ---- Tree Node ----
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* createNode(int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

// ---- Queue for Node Pointers ----
typedef struct {
    Node *arr[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) { q->front = q->rear = -1; }
int isQueueEmpty(Queue *q) { return q->front == -1; }

void enqueue(Queue *q, Node *node) {
    if (q->front == -1) q->front = 0;
    q->arr[++q->rear] = node;
}

Node* dequeue(Queue *q) {
    Node *node = q->arr[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front++;
    return node;
}

// ---- Build Tree from Level-Order Input ----
Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1) return NULL;

    Queue q;
    initQueue(&q);

    Node *root = createNode(arr[0]);
    enqueue(&q, root);

    int i = 1;
    while (!isQueueEmpty(&q) && i < n) {
        Node *curr = dequeue(&q);

        if (i < n && arr[i] != -1) {
            curr->left = createNode(arr[i]);
            enqueue(&q, curr->left);
        }
        i++;

        if (i < n && arr[i] != -1) {
            curr->right = createNode(arr[i]);
            enqueue(&q, curr->right);
        }
        i++;
    }

    return root;
}

// ---- Level Order Traversal (BFS) ----
void levelOrder(Node *root) {
    if (root == NULL) return;

    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isQueueEmpty(&q)) {
        Node *curr = dequeue(&q);
        printf("%d ", curr->data);

        if (curr->left != NULL)
            enqueue(&q, curr->left);
        if (curr->right != NULL)
            enqueue(&q, curr->right);
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[MAX];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    Node *root = buildTree(arr, n);

    levelOrder(root);

    return 0;
}
