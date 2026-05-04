#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pq[10005];
int size = 0;

void insert(int val) {
    pq[size++] = val;
}

int deleteMin() {
    if (size == 0) return -1;
    int minIdx = 0;
    for (int i = 1; i < size; i++)
        if (pq[i] < pq[minIdx]) minIdx = i;
    int minVal = pq[minIdx];
    pq[minIdx] = pq[--size]; // last element se replace
    return minVal;
}

int peek() {
    if (size == 0) return -1;
    int minVal = pq[0];
    for (int i = 1; i < size; i++)
        if (pq[i] < minVal) minVal = pq[i];
    return minVal;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        char op[10];
        scanf("%s", op);
        if (strcmp(op, "insert") == 0) {
            int val;
            scanf("%d", &val);
            insert(val);
        } else if (strcmp(op, "delete") == 0) {
            printf("%d\n", deleteMin());
        } else if (strcmp(op, "peek") == 0) {
            printf("%d\n", peek());
        }
    }
    return 0;
}
