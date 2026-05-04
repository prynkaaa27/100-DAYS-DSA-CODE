// Day 53: Vertical Order Traversal of a Binary Tree
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

// ---- Queue for BFS (stores node and its horizontal distance) ----
typedef struct {
    Node *node;
    int hd;  // horizontal distance from root
} QItem;

typedef struct {
    QItem arr[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) { q->front = q->rear = -1; }
int isQueueEmpty(Queue *q) { return q->front == -1; }

void enqueue(Queue *q, Node *node, int hd) {
    if (q->front == -1) q->front = 0;
    q->arr[++q->rear].node = node;
    q->arr[q->rear].hd = hd;
}

QItem dequeue(Queue *q) {
    QItem item = q->arr[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front++;
    return item;
}

// ---- Build Tree from Level-Order ----
Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1) return NULL;

    Queue q;
    initQueue(&q);

    Node *root = createNode(arr[0]);
    enqueue(&q, root, 0);

    int i = 1;
    while (!isQueueEmpty(&q) && i < n) {
        QItem curr = dequeue(&q);

        if (i < n && arr[i] != -1) {
            curr.node->left = createNode(arr[i]);
            enqueue(&q, curr.node->left, 0);
        }
        i++;

        if (i < n && arr[i] != -1) {
            curr.node->right = createNode(arr[i]);
            enqueue(&q, curr.node->right, 0);
        }
        i++;
    }

    return root;
}

// ---- Find min and max horizontal distance ----
void findMinMax(Node *root, int hd, int *minHD, int *maxHD) {
    if (root == NULL) return;

    if (hd < *minHD) *minHD = hd;
    if (hd > *maxHD) *maxHD = hd;

    findMinMax(root->left, hd - 1, minHD, maxHD);
    findMinMax(root->right, hd + 1, minHD, maxHD);
}

// ---- Vertical Order Traversal using BFS ----
void verticalOrder(Node *root) {
    if (root == NULL) return;

    // Step 1: Find range of horizontal distances
    int minHD = 0, maxHD = 0;
    findMinMax(root, 0, &minHD, &maxHD);

    // Step 2: For each vertical line, do BFS and collect matching nodes
    for (int line = minHD; line <= maxHD; line++) {
        Queue q;
        initQueue(&q);
        enqueue(&q, root, 0);

        while (!isQueueEmpty(&q)) {
            QItem curr = dequeue(&q);

            if (curr.hd == line)
                printf("%d ", curr.node->data);

            if (curr.node->left)
                enqueue(&q, curr.node->left, curr.hd - 1);
            if (curr.node->right)
                enqueue(&q, curr.node->right, curr.hd + 1);
        }
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[MAX];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    Node *root = buildTree(arr, n);

    verticalOrder(root);

    return 0;
}
