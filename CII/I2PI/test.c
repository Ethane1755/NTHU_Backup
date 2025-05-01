#include <stdio.h>

int maxBit (int x) {
    int temp = 0;
    while (x > 1) {
        x /= 2;
        temp++;
    }
    return temp;
}

int main () {
    int N, m, x;
    scanf("%d", &N);
    while (N--) {
        int ans = 0;
        int bit[32] = {0};
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d", &x);
            bit[maxBit(x)]++;
        }
        for (int i = 0; i < 32; i++) {
            ans += bit[i] * (bit[i] - 1) / 2;
        }
        printf("%d\n", ans);
    }

    return 0;
}