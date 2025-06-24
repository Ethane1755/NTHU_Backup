#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double l, r;
} Interval;

int cmp(const void *a, const void *b) {
    Interval *ia = (Interval *)a;
    Interval *ib = (Interval *)b;
    if (ia->l < ib->l) return -1;
    if (ia->l > ib->l) return 1;
    if (ia->r < ib->r) return -1;
    if (ia->r > ib->r) return 1;
    return 0;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        double N;
        int Q;
        scanf("%lf %d", &N, &Q);
        Interval *arr = (Interval *)malloc(Q * sizeof(Interval));
        for (int i = 0; i < Q; ++i) {
            scanf("%lf %lf", &arr[i].l, &arr[i].r);
        }
        qsort(arr, Q, sizeof(Interval), cmp);

        double covered = 0.0;
        double cur_l = -1, cur_r = -1;
        for (int i = 0; i < Q; ++i) {
            if (arr[i].l > cur_r) {
                // New interval, add previous
                if (cur_r >= 0) covered += cur_r - cur_l;
                cur_l = arr[i].l;
                cur_r = arr[i].r;
            } else {
                // Overlap, extend
                if (arr[i].r > cur_r) cur_r = arr[i].r;
            }
        }
        if (cur_r >= 0) covered += cur_r - cur_l;
        double safe = (N - covered) / N;
        if (safe < 0) safe = 0;
        printf("%.6lf\n", safe);
        free(arr);
    }
    return 0;
}