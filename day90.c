#include <stdio.h>

// Check if we can paint within maxTime using k painters
int isPossible(int boards[], int n, int k, int maxTime) {
    int painters = 1;
    int currTime = 0;

    for (int i = 0; i < n; i++) {
        if (boards[i] > maxTime)
            return 0;

        if (currTime + boards[i] > maxTime) {
            painters++;
            currTime = boards[i];
        } else {
            currTime += boards[i];
        }
    }
    return painters <= k;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int boards[n];
    int sum = 0, maxVal = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &boards[i]);
        sum += boards[i];
        if (boards[i] > maxVal)
            maxVal = boards[i];
    }

    int low = maxVal, high = sum, ans = sum;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (isPossible(boards, n, k, mid)) {
            ans = mid;
            high = mid - 1; // minimize time
        } else {
            low = mid + 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}