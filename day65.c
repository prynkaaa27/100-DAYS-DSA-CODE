// Day 65: Cycle Detection in Undirected Graph using DFS
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

// ---- DFS with Parent Tracking for Cycle Detection ----
int visited[MAX];

int dfsCycle(Graph *g, int v, int parent) {
    visited[v] = 1;

    AdjNode *curr = g->adjList[v];
    while (curr != NULL) {
        if (!visited[curr->vertex]) {
            // Visit unvisited neighbor
            if (dfsCycle(g, curr->vertex, v))
                return 1;  // Cycle found in subtree
        }
        else if (curr->vertex != parent) {
            // Visited neighbor that is NOT parent = CYCLE
            return 1;
        }
        curr = curr->next;
    }

    return 0;  // No cycle found
}

// ---- Check all components (handles disconnected graphs) ----
int hasCycle(Graph *g) {
    for (int i = 0; i < g->numVertices; i++)
        visited[i] = 0;

    for (int i = 0; i < g->numVertices; i++) {
        if (!visited[i]) {
            if (dfsCycle(g, i, -1))
                return 1;
        }
    }
    return 0;
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

    if (hasCycle(g))
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}
