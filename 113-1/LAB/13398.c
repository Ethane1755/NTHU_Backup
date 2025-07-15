#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100
#define STRING_LENGTH 6

int charOrder[26];

void sortString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (charOrder[str[i] - 'a'] > charOrder[str[j] - 'a']) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int compareStrings(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
}

int main() {
    int N;
    char V[27], strings[MAX_N][STRING_LENGTH + 1];

    scanf("%d", &N);
    scanf("%s", V);
    for (int i = 0; i < N; i++) {
        scanf("%s", strings[i]);
    }

    for (int i = 0; i < 26; i++) {
        charOrder[V[i] - 'a'] = i;
    }

    for (int i = 0; i < N; i++) {
        sortString(strings[i]);
    }

    qsort(strings, N, sizeof(strings[0]), compareStrings);

    for (int i = 0; i < N; i++) {
        printf("%s", strings[i]);
        if (i != N - 1) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}