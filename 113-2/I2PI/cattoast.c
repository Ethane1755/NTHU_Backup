#include <stdio.h>
#include <math.h>

int n, r;
int x[10001], y[10001], flag[10001];

int dist(int x, int y, int x1, int y1) {
    if (sqrt((x - x1)*(x - x1) + (y - y1)*(y - y1)) > r) return 0;
    return 1;
}

void dfs(int u, int* size) {
    flag[u] = 1;
    (*size)++;
    for (int v = 0; v < n; v++) {
        if (!flag[v] && dist(x[u], y[u], x[v], y[v])) {
            dfs(v, size);
        }
    }
}

int main () {
    scanf("%d %d", &n, &r);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
        flag[i] = 0;
    }
    int remain = 0, blackhole = 0;
    for (int i = 0; i < n; i++) {
        if (!flag[i]) {
            int size = 0;
            dfs(i, &size);
            if (size == 1) remain++;
            else blackhole++;
        }
    }
    printf("%d %d\n", remain, blackhole);
    return 0;
}