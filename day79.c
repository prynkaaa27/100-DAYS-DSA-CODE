#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF 1000000000

typedef struct {
    int v, w;
} Node;

Node adj[MAX][MAX];
int adjSize[MAX];

// Min heap node
typedef struct {
    int v, dist;
} HeapNode;

HeapNode heap[MAX * MAX];
int heapSize = 0;

// swap
void swap(HeapNode *a, HeapNode *b) {
    HeapNode t = *a;
    *a = *b;
    *b = t;
}

// push
void push(int v, int dist) {
    heap[heapSize] = (HeapNode){v, dist};
    int i = heapSize++;
    
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].dist <= heap[i].dist) break;
        swap(&heap[p], &heap[i]);
        i = p;
    }
}

// pop
HeapNode pop() {
    HeapNode root = heap[0];
    heap[0] = heap[--heapSize];

    int i = 0;
    while (1) {
        int smallest = i;
        int l = 2*i + 1, r = 2*i + 2;

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

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
        adjSize[i] = 0;

    // input edges
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        adj[u][adjSize[u]].v = v;
        adj[u][adjSize[u]].w = w;
        adjSize[u]++;

        adj[v][adjSize[v]].v = u;
        adj[v][adjSize[v]].w = w;
        adjSize[v]++;
    }

    int src;
    scanf("%d", &src);

    int dist[MAX];

    for (int i = 1; i <= n; i++)
        dist[i] = INF;

    dist[src] = 0;
    push(src, 0);

    while (heapSize > 0) {
        HeapNode cur = pop();
        int u = cur.v;

        if (cur.dist > dist[u]) continue;

        for (int i = 0; i < adjSize[u]; i++) {
            int v = adj[u][i].v;
            int w = adj[u][i].w;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                push(v, dist[v]);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF)
            printf("INF ");
        else
            printf("%d ", dist[i]);
    }

    return 0;
}