#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int heap[MAX];
int size = 0;

// Swap function
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify Up
void heapifyUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent] > heap[i]) {
            swap(&heap[parent], &heap[i]);
            i = parent;
        } else break;
    }
}

// Heapify Down
void heapifyDown(int i) {
    int smallest = i;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && heap[left] < heap[smallest])
            smallest = left;

        if (right < size && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != i) {
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        } else break;
    }
}

// Insert
void insert(int x) {
    if (size == MAX) return;

    heap[size] = x;
    heapifyUp(size);
    size++;
}

// Peek
int peek() {
    if (size == 0) return -1;
    return heap[0];
}

// Extract Min
int extractMin() {
    if (size == 0) return -1;

    int root = heap[0];
    heap[0] = heap[size - 1];
    size--;

    heapifyDown(0);
    return root;
}

// Main
int main() {
    int n;
    scanf("%d", &n);

    while (n--) {
        char op[20];
        scanf("%s", op);

        if (op[0] == 'i') { // insert
            int x;
            scanf("%d", &x);
            insert(x);
        }
        else if (op[0] == 'p') { // peek
            printf("%d\n", peek());
        }
        else if (op[0] == 'e') { // extractMin
            printf("%d\n", extractMin());
        }
    }

    return 0;
}