// Day 52: Lowest Common Ancestor (LCA) in a Binary Tree
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

// ---- Find LCA in Binary Tree (Recursive) ----
Node* findLCA(Node *root, int p, int q) {
    // Base case
    if (root == NULL)
        return NULL;

    // If current node matches either p or q, it is the LCA candidate
    if (root->data == p || root->data == q)
        return root;

    // Search in left and right subtrees
    Node *leftLCA = findLCA(root->left, p, q);
    Node *rightLCA = findLCA(root->right, p, q);

    // If both sides return non-NULL, current node is the LCA
    if (leftLCA != NULL && rightLCA != NULL)
        return root;

    // Otherwise return whichever side is non-NULL
    return (leftLCA != NULL) ? leftLCA : rightLCA;
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[MAX];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int p, q;
    scanf("%d %d", &p, &q);

    Node *root = buildTree(arr, n);

    Node *lca = findLCA(root, p, q);
    if (lca != NULL)
        printf("%d\n", lca->data);

    return 0;
}
