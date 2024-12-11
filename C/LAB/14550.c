#include <stdio.h>

int find (int n) {
    int k[10001];
    for (int i = 0; i < n; i++) {
        k[i] = n*i;
    }
    return k;
}

int jump (int n, int m, int color[], int weight[]) {
    int c_sum, w_sum;


}

int main () {
    int n, q, m;
    scanf("%d %d", &n, &q);
    int color[10001], weight[10001];
    for (int i = 0; i < n; i++) {
        scanf("%d", &color[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &weight[i]);
    }
    for (int i = 0; i < q; i++)
    {
        scanf("%d", &m);
    }
    return 0;
}