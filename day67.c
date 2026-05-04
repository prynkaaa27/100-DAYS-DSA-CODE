// Day 67: Topological Sort of a DAG using DFS
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

// ---- Stack for storing topological order ----
int stack[MAX];
int top = -1;

void push(int val) { stack[++top] = val; }
int pop() { return stack[top--]; }

// ---- DFS for Topological Sort ----
int visited[MAX];

void dfs(Graph *g, int v) {
    visited[v] = 1;

    AdjNode *curr = g->adjList[v];
    while (curr != NULL) {
        if (!visited[curr->vertex])
            dfs(g, curr->vertex);
        curr = curr->next;
    }

    // Push to stack AFTER all neighbors are processed
    push(v);
}

// ---- Topological Sort ----
void topologicalSort(Graph *g) {
    for (int i = 0; i < g->numVertices; i++)
        visited[i] = 0;

    // Run DFS for all unvisited vertices
    for (int i = 0; i < g->numVertices; i++) {
        if (!visited[i])
            dfs(g, i);
    }

    // Print stack (topological order)
    while (top != -1)
        printf("%d ", pop());
    printf("\n");
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

    topologicalSort(g);

    return 0;
}
