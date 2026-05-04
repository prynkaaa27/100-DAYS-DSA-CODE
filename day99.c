#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pos;
    int speed;
    double time;
} Car;

// sort by position descending
int cmp(const void *a, const void *b) {
    return ((Car*)b)->pos - ((Car*)a)->pos;
}

int main() {
    int n, target;
    scanf("%d %d", &n, &target);

    Car cars[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &cars[i].pos);

    for (int i = 0; i < n; i++)
        scanf("%d", &cars[i].speed);

    // compute time to reach target
    for (int i = 0; i < n; i++) {
        cars[i].time = (double)(target - cars[i].pos) / cars[i].speed;
    }

    // sort by position descending
    qsort(cars, n, sizeof(Car), cmp);

    int fleets = 0;
    double lastTime = 0.0;

    for (int i = 0; i < n; i++) {
        if (cars[i].time > lastTime) {
            fleets++;
            lastTime = cars[i].time;
        }
    }

    printf("%d\n", fleets);
    return 0;
}