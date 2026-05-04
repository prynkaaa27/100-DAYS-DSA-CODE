#include <stdio.h>

#define MAX 100000

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // We'll use a simple array-based hash (offset for negatives)
    // Shift prefix sum range to avoid negative indexing
    int offset = MAX;
    int hash[2 * MAX];
    
    for (int i = 0; i < 2 * MAX; i++)
        hash[i] = -2;   // uninitialized marker

    int prefixSum = 0;
    int maxLen = 0;

    // prefix sum 0 occurs at index -1
    hash[offset] = -1;

    for (int i = 0; i < n; i++) {
        prefixSum += arr[i];

        int idx = prefixSum + offset;

        if (hash[idx] != -2) {
            int len = i - hash[idx];
            if (len > maxLen)
                maxLen = len;
        } else {
            hash[idx] = i;
        }
    }

    printf("%d\n", maxLen);

    return 0;
}