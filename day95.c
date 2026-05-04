#include <stdio.h>
#include <stdlib.h>

// Insertion sort for each bucket
void insertionSort(float bucket[], int size) {
    for (int i = 1; i < size; i++) {
        float key = bucket[i];
        int j = i - 1;

        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

void bucketSort(float arr[], int n) {
    // Create buckets
    float buckets[n][n];   // worst case each bucket may hold n elements
    int count[n];

    for (int i = 0; i < n; i++)
        count[i] = 0;

    // Step 1: distribute elements
    for (int i = 0; i < n; i++) {
        int idx = n * arr[i];   // bucket index
        buckets[idx][count[idx]++] = arr[i];
    }

    // Step 2: sort each bucket
    for (int i = 0; i < n; i++) {
        if (count[i] > 0)
            insertionSort(buckets[i], count[i]);
    }

    // Step 3: concatenate
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < count[i]; j++) {
            arr[k++] = buckets[i][j];
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    float arr[n];
    for (int i = 0; i < n; i++)
        scanf("%f", &arr[i]);

    bucketSort(arr, n);

    for (int i = 0; i < n; i++)
        printf("%.6f ", arr[i]);

    return 0;
}