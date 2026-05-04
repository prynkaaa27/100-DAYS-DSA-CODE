#include <stdio.h>
#include <string.h>

#define MAX 256

int main() {
    char s[1000];
    scanf("%s", s);

    int firstIndex[MAX];
    for (int i = 0; i < MAX; i++)
        firstIndex[i] = -1;

    int ansIndex = 1000000;   // large value
    char ans = -1;

    for (int i = 0; s[i] != '\0'; i++) {
        unsigned char ch = s[i];

        if (firstIndex[ch] == -1) {
            firstIndex[ch] = i;
        } else {
            // repeated character found
            if (i < ansIndex) {
                ansIndex = i;
                ans = ch;
            }
        }
    }

    if (ans == -1)
        printf("-1\n");
    else
        printf("%c\n", ans);

    return 0;
}