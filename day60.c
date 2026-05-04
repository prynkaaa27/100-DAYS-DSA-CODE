// Day 60: Check if a Binary Tree satisfies Min-Heap Property
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// ---- Check Min-Heap using Array (Level-Order) ----
// In a complete binary tree stored as array:
// Parent of i -> (i-1)/2
// Left child of i -> 2*i + 1
// Right child of i -> 2*i + 2
// Min-Heap: parent <= both children

int isMinHeap(int arr[], int n) {
    // Check all non-leaf nodes (from 0 to n/2 - 1)
    for (int i = 0; i <= (n - 2) / 2; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // Check left child
        if (left < n && arr[i] > arr[left])
            return 0;

        // Check right child
        if (right < n && arr[i] > arr[right])
            return 0;
    }

    return 1;
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[MAX];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    if (isMinHeap(arr, n))
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}
