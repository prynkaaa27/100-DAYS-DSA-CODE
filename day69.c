#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF INT_MAX

// Min Heap Node
typedef struct {
    int v;
    int dist;
} Node;

Node heap[MAX];
int heapSize = 0;

// Swap
void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify up
void push(Node n) {
    heap[heapSize] = n;
    int i = heapSize;
    heapSize++;

    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent].dist <= heap[i].dist) break;
        swap(&heap[parent], &heap[i]);
        i = parent;
    }
}

// Heapify down
Node pop() {
    Node root = heap[0];
    heap[0] = heap[--heapSize];

    int i = 0;
    while (1) {
        int smallest = i;
        int l = 2*i + 1;
        int r = 2*i + 2;

        if (l < heapSize && heap[l].dist < heap[smallest].dist)
            smallest = l;
        if (r < heapSize && heap[r].dist < heap[smallest].dist)
            smallest = r;

        if (smallest == i) break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }

    return root;
}

// Dijkstra
void dijkstra(int V, int adj[MAX][MAX], int src) {
    int dist[MAX];

    for (int i = 0; i < V; i++)
        dist[i] = INF;

    dist[src] = 0;

    push((Node){src, 0});

    while (heapSize > 0) {
        Node current = pop();
        int u = current.v;

        // ignore outdated entries
        if (current.dist > dist[u]) continue;

        for (int v = 0; v < V; v++) {
            if (adj[u][v] != 0) {
                int weight = adj[u][v];

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    push((Node){v, dist[v]});
                }
            }
        }
    }

    // Print result
    printf("Shortest distances from source %d:\n", src);
    for (int i = 0; i < V; i++) {
        printf("%d -> %d\n", i, dist[i]);
    }
}

// Driver
int main() {
    int V = 5;

    int adj[MAX][MAX] = {0};

    // Weighted graph
    adj[0][1] = 10;
    adj[0][4] = 5;
    adj[1][2] = 1;
    adj[1][4] = 2;
    adj[2][3] = 4;
    adj[3][2] = 6;
    adj[4][1] = 3;
    adj[4][2] = 9;
    adj[4][3] = 2;

    dijkstra(V, adj, 0);

    return 0;
}
