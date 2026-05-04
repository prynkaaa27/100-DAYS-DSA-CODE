// Day 56: Check if a Binary Tree is Symmetric (Mirror of Itself)
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

// ---- Queue for Tree Construction ----
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

// ---- Build Tree from Level-Order ----
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

// ---- Check if Two Subtrees are Mirror ----
int isMirror(Node *left, Node *right) {
    // Both NULL -> symmetric
    if (left == NULL && right == NULL)
        return 1;

    // One NULL, other not -> not symmetric
    if (left == NULL || right == NULL)
        return 0;

    // Values must match AND subtrees must be mirrors
    return (left->data == right->data)
        && isMirror(left->left, right->right)
        && isMirror(left->right, right->left);
}

// ---- Check if Tree is Symmetric ----
int isSymmetric(Node *root) {
    if (root == NULL)
        return 1;
    return isMirror(root->left, root->right);
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[MAX];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    Node *root = buildTree(arr, n);

    if (isSymmetric(root))
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}
