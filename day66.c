// Day 66: Cycle Detection in Directed Graph using DFS + Recursion Stack
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

// ---- Add Edge (Directed) ----
void addEdge(Graph *g, int u, int v) {
    AdjNode *node = createNode(v);
    node->next = g->adjList[u];
    g->adjList[u] = node;
}

// ---- DFS with Recursion Stack ----
int visited[MAX];
int recStack[MAX];  // tracks nodes in current DFS path

int dfsCycle(Graph *g, int v) {
    visited[v] = 1;
    recStack[v] = 1;  // add to current path

    AdjNode *curr = g->adjList[v];
    while (curr != NULL) {
        if (!visited[curr->vertex]) {
            if (dfsCycle(g, curr->vertex))
                return 1;
        }
        else if (recStack[curr->vertex]) {
            // Neighbor is in current DFS path = BACK EDGE = CYCLE
            return 1;
        }
        curr = curr->next;
    }

    recStack[v] = 0;  // remove from current path (backtrack)
    return 0;
}

// ---- Check all vertices ----
int hasCycle(Graph *g) {
    for (int i = 0; i < g->numVertices; i++) {
        visited[i] = 0;
        recStack[i] = 0;
    }

    for (int i = 0; i < g->numVertices; i++) {
        if (!visited[i]) {
            if (dfsCycle(g, i))
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
