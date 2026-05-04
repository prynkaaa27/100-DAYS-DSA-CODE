// Day 58: Construct Binary Tree from Preorder and Inorder Traversals
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

// ---- Find index of a value in inorder array ----
int findIndex(int inorder[], int start, int end, int val) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == val)
            return i;
    }
    return -1;
}

// ---- Build Tree from Preorder and Inorder ----
int preIndex = 0;  // global index for preorder array

Node* buildTree(int preorder[], int inorder[], int inStart, int inEnd) {
    if (inStart > inEnd)
        return NULL;

    // Pick current node from preorder (root of current subtree)
    Node *root = createNode(preorder[preIndex++]);

    // If this node has no children, return
    if (inStart == inEnd)
        return root;

    // Find position of this node in inorder array
    int inIndex = findIndex(inorder, inStart, inEnd, root->data);

    // Build left subtree (elements before inIndex in inorder)
    root->left = buildTree(preorder, inorder, inStart, inIndex - 1);

    // Build right subtree (elements after inIndex in inorder)
    root->right = buildTree(preorder, inorder, inIndex + 1, inEnd);

    return root;
}

// ---- Postorder Traversal ----
void postorder(Node *root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int main() {
    int n;
    scanf("%d", &n);

    int pre[MAX], in[MAX];

    for (int i = 0; i < n; i++)
        scanf("%d", &pre[i]);

    for (int i = 0; i < n; i++)
        scanf("%d", &in[i]);

    preIndex = 0;
    Node *root = buildTree(pre, in, 0, n - 1);

    postorder(root);
    printf("\n");

    return 0;
}
