#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int main() {
    int n;
    scanf("%d", &n);

    long long arr[n];
    for(int i = 0; i < n; i++)
        scanf("%lld", &arr[i]);

    long long prefixSum = 0;
    long long count = 0;

    // Using hash-like array (for simplicity assume prefix sum range manageable)
    long long freq[2 * MAX + 1] = {0};
    int offset = MAX;

    freq[offset] = 1;  // To handle subarrays starting from index 0

    for(int i = 0; i < n; i++) {
        prefixSum += arr[i];

        if(freq[prefixSum + offset] > 0)
            count += freq[prefixSum + offset];

        freq[prefixSum + offset]++;
    }

    printf("%lld\n", count);

    return 0;
}