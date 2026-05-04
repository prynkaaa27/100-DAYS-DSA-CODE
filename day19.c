#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function for qsort (ascending order)
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];

    // Input array
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Sort the array
    qsort(arr, n, sizeof(int), compare);

    int left = 0;
    int right = n - 1;

    int min_sum = INT_MAX;
    int min_left = 0, min_right = 0;

    // Two pointer approach
    while(left < right) {
        int sum = arr[left] + arr[right];

        if(abs(sum) < abs(min_sum)) {
            min_sum = sum;
            min_left = left;
            min_right = right;
        }

        if(sum < 0)
            left++;
        else
            right--;
    }

    printf("%d %d\n", arr[min_left], arr[min_right]);

    return 0;
}
