#include <stdio.h>
#include <string.h>

int n;
int p[100001];
int bit[32];

int maxBit (int x) {
    int a = 0;
    while (x > 0) {
        x /= 2;
        ++a;
    }
    return a;
}

void solve () {
    memset(bit, 0, sizeof(bit));
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &p[i]);
    }
    for (int i = 0; i < n; ++i) {
        ++bit[maxBit(p[i])];
    }
    long long ans = 0;
    for (int i = 0; i < 32; ++i) {
        ans += (long long)bit[i] * (bit[i] - 1) / 2;
    }
    printf("%lld\n", ans);
}

int main () {
    int T;
    scanf("%d", &T);
    while (T--) solve();
    return 0;
}