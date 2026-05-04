// Day 62: Graph Representation using Adjacency List (Linked List)
#include <stdio.h>
#include <stdlib.h>

// ---- Adjacency List Node ----
typedef struct AdjNode {
    int vertex;
    struct AdjNode *next;
} AdjNode;

// ---- Graph Structure ----
typedef struct {
    int numVertices;
    AdjNode **adjList;  // array of linked list heads
} Graph;

// ---- Create a new adjacency node ----
AdjNode* createNode(int v) {
    AdjNode *node = (AdjNode *)malloc(sizeof(AdjNode));
    node->vertex = v;
    node->next = NULL;
    return node;
}

// ---- Create Graph with n vertices ----
Graph* createGraph(int n) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->numVertices = n;
    g->adjList = (AdjNode **)malloc(n * sizeof(AdjNode *));

    for (int i = 0; i < n; i++)
        g->adjList[i] = NULL;

    return g;
}

// ---- Add Edge (Undirected) ----
void addEdge(Graph *g, int u, int v) {
    // Add v to u's list
    AdjNode *node = createNode(v);
    node->next = g->adjList[u];
    g->adjList[u] = node;

    // Add u to v's list (remove for directed graph)
    node = createNode(u);
    node->next = g->adjList[v];
    g->adjList[v] = node;
}

// ---- Print Adjacency List ----
void printGraph(Graph *g) {
    for (int i = 0; i < g->numVertices; i++) {
        printf("%d -> ", i);
        AdjNode *curr = g->adjList[i];
        while (curr != NULL) {
            printf("%d ", curr->vertex);
            curr = curr->next;
        }
        printf("\n");
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Graph *g = createGraph(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(g, u, v);
    }

    printGraph(g);

    return 0;
}
