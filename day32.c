#include <stdio.h>
#define MAX 100

int main() {
    int n, m;
    int stack[MAX];
    int top = -1;

    // Read number of elements to push
    scanf("%d", &n);

    // Push elements
    for (int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        
        if (top < MAX - 1) {
            stack[++top] = value;
        }
    }

    // Read number of pops
    scanf("%d", &m);

    // Pop elements
    for (int i = 0; i < m; i++) {
        if (top >= 0) {
            top--;
        }
    }

    // Print remaining stack from top to bottom
    for (int i = top; i >= 0; i--) {
        printf("%d ", stack[i]);
    }

    return 0;
}