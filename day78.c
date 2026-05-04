#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF 1000000000

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int graph[MAX][MAX];

    // initialize graph
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = (i == j) ? 0 : INF;
        }
    }

    // input edges (undirected)
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        if (w < graph[u][v]) { // handle multiple edges
            graph[u][v] = w;
            graph[v][u] = w;
        }
    }

    int visited[MAX] = {0};
    int key[MAX];

    for (int i = 1; i <= n; i++)
        key[i] = INF;

    // start from node 1
    key[1] = 0;

    int totalWeight = 0;

    for (int count = 1; count <= n; count++) {

        int min = INF, u = -1;

        // pick minimum key vertex not in MST
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        visited[u] = 1;
        totalWeight += key[u];

        // update neighbors
        for (int v = 1; v <= n; v++) {
            if (graph[u][v] < key[v] && !visited[v]) {
                key[v] = graph[u][v];
            }
        }
    }

    printf("%d\n", totalWeight);

    return 0;
}