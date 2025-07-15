#include <stdio.h>

int n, k, ans = 0;
int a[21];

void dfs(int idx, int sum) {
    if (idx == n) {
        if (sum == k) ans++;
        return;
    }
    // Include a[idx]
    dfs(idx + 1, sum + a[idx]);
    // Exclude a[idx]
    dfs(idx + 1, sum);
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    dfs(0, 0);
    printf("%d\n", ans);
    return 0;
}