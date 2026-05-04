#include <stdio.h>
#include <string.h>

#define MAX 1000

int main() {
    int n;
    scanf("%d", &n);

    char names[MAX][50];
    int freq[MAX] = {0};
    int unique = 0;

    for (int i = 0; i < n; i++) {
        char name[50];
        scanf("%s", name);

        int found = -1;

        // check if already exists
        for (int j = 0; j < unique; j++) {
            if (strcmp(names[j], name) == 0) {
                found = j;
                break;
            }
        }

        if (found != -1) {
            freq[found]++;
        } else {
            strcpy(names[unique], name);
            freq[unique] = 1;
            unique++;
        }
    }

    int maxVotes = 0;
    char winner[50] = "";

    for (int i = 0; i < unique; i++) {
        if (freq[i] > maxVotes) {
            maxVotes = freq[i];
            strcpy(winner, names[i]);
        } 
        else if (freq[i] == maxVotes) {
            if (strcmp(names[i], winner) < 0) {
                strcpy(winner, names[i]);
            }
        }
    }

    printf("%s %d\n", winner, maxVotes);

    return 0;
}
