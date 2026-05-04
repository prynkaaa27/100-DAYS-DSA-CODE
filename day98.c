#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start, end;
} Interval;

int cmp(const void *a, const void *b) {
    Interval *i1 = (Interval *)a;
    Interval *i2 = (Interval *)b;
    return i1->start - i2->start;
}

void mergeIntervals(Interval arr[], int n) {
    if (n == 0) return;

    // Step 1: Sort intervals
    qsort(arr, n, sizeof(Interval), cmp);

    // Step 2: Merge
    Interval res[n];
    int index = 0;

    res[0] = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i].start <= res[index].end) {
            // Overlap → merge
            if (arr[i].end > res[index].end)
                res[index].end = arr[i].end;
        } else {
            // No overlap → new interval
            index++;
            res[index] = arr[i];
        }
    }

    // Print result
    for (int i = 0; i <= index; i++) {
        printf("%d %d\n", res[i].start, res[i].end);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    Interval arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].start, &arr[i].end);
    }

    mergeIntervals(arr, n);
    return 0;
}