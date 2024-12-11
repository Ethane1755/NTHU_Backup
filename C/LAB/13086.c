#include <stdio.h>
#include <string.h>

void find(int n, int k, char c1[2001], char c2[2001]) {
    // Calculate lengths of F0 and F1
    unsigned long long len[60];
    len[0] = strlen(c1);
    len[1] = strlen(c2);

    // Calculate lengths of Fn up to the required n
    for (int i = 2; i <= n; i++) {
        len[i] = len[i-2] + len[i-1];
    }
    // c1

    if (n % 2 == 0) {
        for (int i = n; i >= 0; i--) {
            if (k <= len[0]) {
                printf("%c\n", c1[k]);
                break;
            } else {
                k -= (len[i] - len[i-1]);
                printf("%d %llu %llu\n", k, len[i], len[i-1]);
            }
        }
    } else if (n % 2 != 0) {
        for (int i = n; i >= 0; i--) {
            if (k <= len[1]) {
                printf("%c\n", c2[k]);
                break;
            } else {
                k -= (len[i] - len[i-1]);
                printf("%d\n", k);
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        char F0[2001], F1[2001];
        int n, k;
        scanf("%s %s", F0, F1);
        scanf("%d %d", &n, &k);
        find(n, k, F0, F1);
    }
    return 0;
}