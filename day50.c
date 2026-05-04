// Day 50: Search in a Binary Search Tree (BST)
#include <stdio.h>
#include <stdlib.h>

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

// ---- BST Insert ----
Node* insert(Node *root, int val) {
    if (root == NULL)
        return createNode(val);

    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);

    return root;
}

// ---- BST Search (Recursive) ----
int search(Node *root, int key) {
    if (root == NULL)
        return 0;  // Not found

    if (key == root->data)
        return 1;  // Found

    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

int main() {
    int n;
    scanf("%d", &n);

    Node *root = NULL;
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        root = insert(root, val);
    }

    int key;
    scanf("%d", &key);

    if (search(root, key))
        printf("Found\n");
    else
        printf("Not Found\n");

    return 0;
}
