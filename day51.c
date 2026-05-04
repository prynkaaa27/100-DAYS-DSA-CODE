// Day 51: Lowest Common Ancestor (LCA) in a Binary Search Tree
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

// ---- Find LCA in BST ----
Node* findLCA(Node *root, int p, int q) {
    if (root == NULL)
        return NULL;

    // Both nodes are in the left subtree
    if (p < root->data && q < root->data)
        return findLCA(root->left, p, q);

    // Both nodes are in the right subtree
    if (p > root->data && q > root->data)
        return findLCA(root->right, p, q);

    // Split point: one on left, one on right (or one is root)
    return root;
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

    int p, q;
    scanf("%d %d", &p, &q);

    Node *lca = findLCA(root, p, q);
    if (lca != NULL)
        printf("%d\n", lca->data);

    return 0;
}
