// Day 64: Breadth First Search (BFS) using Queue
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

// ---- Queue for BFS ----
typedef struct {
    int arr[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) { q->front = q->rear = -1; }
int isQueueEmpty(Queue *q) { return q->front == -1; }

void enqueue(Queue *q, int val) {
    if (q->front == -1) q->front = 0;
    q->arr[++q->rear] = val;
}

int dequeue(Queue *q) {
    int val = q->arr[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front++;
    return val;
}

// ---- BFS Traversal ----
void bfs(Graph *g, int s) {
    int visited[MAX] = {0};

    Queue q;
    initQueue(&q);

    visited[s] = 1;
    enqueue(&q, s);

    while (!isQueueEmpty(&q)) {
        int curr = dequeue(&q);
        printf("%d ", curr);

        AdjNode *temp = g->adjList[curr];
        while (temp != NULL) {
            if (!visited[temp->vertex]) {
                visited[temp->vertex] = 1;
                enqueue(&q, temp->vertex);
            }
            temp = temp->next;
        }
    }
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

    int s;
    scanf("%d", &s);

    bfs(g, s);

    return 0;
}
