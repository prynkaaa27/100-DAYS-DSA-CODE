#include <stdio.h>

#define MAX 1000

int adj[MAX][MAX];
int visited[MAX];

void dfs(int node, int n) {
    visited[node] = 1;

    for (int i = 1; i <= n; i++) {
        if (adj[node][i] == 1 && !visited[i]) {
            dfs(i, n);
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // initialize
    for (int i = 0; i < MAX; i++) {
        visited[i] = 0;
        for (int j = 0; j < MAX; j++) {
            adj[i][j] = 0;
        }
    }

    // build undirected graph
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    // start DFS from node 1
    dfs(1, n);

    // check if all visited
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            printf("NOT CONNECTED\n");
            return 0;
        }
    }

    printf("CONNECTED\n");

    return 0;
}