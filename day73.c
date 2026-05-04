#include <stdio.h>
#include <string.h>

#define MAX 256

int main() {
    char s[1000];
    scanf("%s", s);

    int freq[MAX] = {0};

    // Step 1: Count frequency
    for (int i = 0; s[i] != '\0'; i++) {
        freq[(unsigned char)s[i]]++;
    }

    // Step 2: Find first non-repeating character
    for (int i = 0; s[i] != '\0'; i++) {
        if (freq[(unsigned char)s[i]] == 1) {
            printf("%c\n", s[i]);
            return 0;
        }
    }

    // Step 3: If none found
    printf("$\n");

    return 0;
}