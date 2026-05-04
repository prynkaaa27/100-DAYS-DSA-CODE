#include <stdio.h>

// Iterative Binary Search
int binarySearch(int arr[], int n, int x) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == x)
            return mid;
        else if (arr[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1; // not found
}

int main() {
    int n, x;

    scanf("%d", &n);
    int arr[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    scanf("%d", &x); // target value

    int result = binarySearch(arr, n, x);

    if (result != -1)
        printf("%d\n", result);
    else
        printf("-1\n");

    return 0;
}