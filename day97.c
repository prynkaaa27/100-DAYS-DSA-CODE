#include <stdio.h>
#include <stdlib.h>

// structure for meeting
typedef struct {
    int start, end;
} Meeting;

// comparator for sorting by start time
int cmp(const void *a, const void *b) {
    return ((Meeting *)a)->start - ((Meeting *)b)->start;
}

// Min Heap functions
void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

void heapifyUp(int heap[], int i) {
    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void heapifyDown(int heap[], int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] < heap[smallest])
        smallest = left;
    if (right < size && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapifyDown(heap, size, smallest);
    }
}

void insertHeap(int heap[], int *size, int val) {
    heap[*size] = val;
    (*size)++;
    heapifyUp(heap, *size - 1);
}

void removeMin(int heap[], int *size) {
    heap[0] = heap[*size - 1];
    (*size)--;
    heapifyDown(heap, *size, 0);
}

int getMin(int heap[]) {
    return heap[0];
}

int main() {
    int n;
    scanf("%d", &n);

    Meeting arr[n];
    for (int i = 0; i < n; i++)
        scanf("%d %d", &arr[i].start, &arr[i].end);

    // sort by start time
    qsort(arr, n, sizeof(Meeting), cmp);

    int heap[n];
    int size = 0;

    // first meeting
    insertHeap(heap, &size, arr[0].end);

    for (int i = 1; i < n; i++) {
        if (arr[i].start >= getMin(heap)) {
            // reuse room
            removeMin(heap, &size);
        }
        // allocate room
        insertHeap(heap, &size, arr[i].end);
    }

    printf("%d\n", size); // number of rooms needed
    return 0;
}