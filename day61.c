// Day 61: Graph Representation using Adjacency Matrix
#include <stdio.h>

#define MAX 100

int adjMatrix[MAX][MAX];

// ---- Initialize Matrix with 0s ----
void initGraph(int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adjMatrix[i][j] = 0;
}

// ---- Add Edge (Undirected) ----
void addEdge(int u, int v) {
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;  // Remove this line for directed graph
}

// ---- Print Adjacency Matrix ----
void printMatrix(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    initGraph(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    printMatrix(n);

    return 0;
}
