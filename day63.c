// Day 63: Depth First Search (DFS) using Recursion
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// ---- Adjacency List Node ----
typedef struct AdjNode {
    int vertex;
    struct AdjNode *next;
} AdjNode;

// ---- Graph Structure ----
typedef struct {
    int numVertices;
    AdjNode **adjList;
} Graph;

AdjNode* createNode(int v) {
    AdjNode *node = (AdjNode *)malloc(sizeof(AdjNode));
    node->vertex = v;
    node->next = NULL;
    return node;
}

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
    AdjNode *node = createNode(v);
    node->next = g->adjList[u];
    g->adjList[u] = node;

    node = createNode(u);
    node->next = g->adjList[v];
    g->adjList[v] = node;
}

// ---- DFS Recursive ----
int visited[MAX];

void dfs(Graph *g, int v) {
    visited[v] = 1;
    printf("%d ", v);

    AdjNode *curr = g->adjList[v];
    while (curr != NULL) {
        if (!visited[curr->vertex])
            dfs(g, curr->vertex);
        curr = curr->next;
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

    int s;
    scanf("%d", &s);

    // Initialize visited array
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    dfs(g, s);
    printf("\n");

    return 0;
}
