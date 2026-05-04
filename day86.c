#include <stdio.h>

int integerSqrt(int n) {
    if (n == 0 || n == 1)
        return n;

    int left = 0, right = n, ans = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Avoid overflow using division
        if (mid <= n / mid) {
            ans = mid;        // mid^2 <= n
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return ans;
}

int main() {
    int n;
    scanf("%d", &n);

    printf("%d\n", integerSqrt(n));

    return 0;
}