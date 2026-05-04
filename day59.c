// Day 59: Construct Binary Tree from Inorder and Postorder Traversals
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

// ---- Build Tree from Inorder and Postorder ----
int postIndex;  // global index for postorder array (traversed from end)

Node* buildTree(int inorder[], int postorder[], int inStart, int inEnd) {
    if (inStart > inEnd)
        return NULL;

    // Pick current node from end of postorder (root of current subtree)
    Node *root = createNode(postorder[postIndex--]);

    // If this node has no children, return
    if (inStart == inEnd)
        return root;

    // Find position of this node in inorder array
    int inIndex = findIndex(inorder, inStart, inEnd, root->data);

    // Build RIGHT subtree first (postorder is L-R-Root, so reverse is Root-R-L)
    root->right = buildTree(inorder, postorder, inIndex + 1, inEnd);

    // Build LEFT subtree
    root->left = buildTree(inorder, postorder, inStart, inIndex - 1);

    return root;
}

// ---- Preorder Traversal ----
void preorder(Node *root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

int main() {
    int n;
    scanf("%d", &n);

    int in[MAX], post[MAX];

    for (int i = 0; i < n; i++)
        scanf("%d", &in[i]);

    for (int i = 0; i < n; i++)
        scanf("%d", &post[i]);

    postIndex = n - 1;
    Node *root = buildTree(in, post, 0, n - 1);

    preorder(root);
    printf("\n");

    return 0;
}
