#include <stdio.h>
#include <string.h>

void find(long long n, long long k, char c1[2001], char c2[2001]) {
    unsigned long long len[1000];
    len[0] = strlen(c1);
    len[1] = strlen(c2);

    for (int i = 2; i <= n; i++) {
        len[i] = len[i-2] + len[i-1];
    }

    while (n > 1) {
        if (k < len[n-2]) {     
            n -= 2;
        } else {
            k -= len[n-2]; 
            n -= 1;
        }
    }

    if (n == 0) {
        printf("%c\n", c1[k]);
    } else {
        printf("%c\n", c2[k]);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        char F0[2001], F1[2001];
        long long n, k;
        scanf("%s %s", F0, F1);
        scanf("%lld %lld", &n, &k);
        find(n, k, F0, F1);
    }
    return 0;
}