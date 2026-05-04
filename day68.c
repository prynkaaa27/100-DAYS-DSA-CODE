#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void topologicalSort(int V, int adj[MAX][MAX]) {
    int indegree[MAX] = {0};
    int queue[MAX], front = 0, rear = 0;
    int topo[MAX], k = 0;

    // Step 1: Compute in-degree
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (adj[i][j] == 1) {
                indegree[j]++;
            }
        }
    }

    // Step 2: Push all nodes with 0 in-degree
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    // Step 3: BFS process
    while (front < rear) {
        int node = queue[front++];
        topo[k++] = node;

        for (int i = 0; i < V; i++) {
            if (adj[node][i] == 1) {
                indegree[i]--;
                if (indegree[i] == 0) {
                    queue[rear++] = i;
                }
            }
        }
    }

    // Step 4: Check cycle
    if (k != V) {
        printf("Cycle detected! Topological sort not possible.\n");
        return;
    }

    // Print result
    printf("Topological Order: ");
    for (int i = 0; i < k; i++) {
        printf("%d ", topo[i]);
    }
    printf("\n");
}

int main() {
    int V = 6;

    // adjacency matrix (DAG example)
    int adj[MAX][MAX] = {0};

    adj[5][2] = 1;
    adj[5][0] = 1;
    adj[4][0] = 1;
    adj[4][1] = 1;
    adj[2][3] = 1;
    adj[3][1] = 1;

    topologicalSort(V, adj);

    return 0;
}