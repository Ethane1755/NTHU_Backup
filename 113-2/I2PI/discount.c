#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005

int price[MAXN];
long long dp[MAXN];

int cmp(const void *a, const void *b) {
    return (*(int*)a) - (*(int*)b);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, p, k;
        scanf("%d %d %d", &n, &p, &k);
        for (int i = 0; i < n; i++) {
            scanf("%d", &price[i]);
        }
        qsort(price, n, sizeof(int), cmp);

        // dp[i]: min cost to buy i products
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            if (i < k) {
                dp[i] = dp[i-1] + price[i-1];
            } else {
                dp[i] = dp[i-k] + price[i-1];
            }
        }

        int ans = 0;
        for (int i = 0; i <= n; i++) {
            if (dp[i] <= p) {
                if (i > ans) ans = i;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}