#include <stdio.h>
#include <string.h>

int main () {
    int n, q;
    int a[100001];
    long long int prefix[100001];
    memset(prefix, 0, sizeof(prefix));
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if (a[i] < 0) a[i] = 0;
        prefix[i] = prefix[i - 1] + a[i];
    }
    while (q--) {
        int l, r, m;
        scanf("%d %d %d", &l, &r, &m);
        printf("%lld\n", prefix[r] - prefix[l-1]);
    }
    return 0;
}