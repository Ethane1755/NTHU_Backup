#include <stdio.h>

void jump (int n, int m, int color[], int weight[], int k) {
    int c_sum, w_sum;
    if (k == m) {
        printf("%d %d\n", &c_sum, &w_sum);
    } else {
        for (int i = 1; i <= n; i++) {
            if (k % i == 0) {
                
            }

        }

    }

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