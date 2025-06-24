#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a, b, diff;
} Item;

Item items[100005];

int cmp(const void *x, const void *y) {
    return ((Item*)x)->diff - ((Item*)y)->diff;
}

int main() {
    int n, k, ans = 0;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", &items[i].a);
    for (int i = 0; i < n; i++) {
        scanf("%d", &items[i].b);
        items[i].diff = items[i].a - items[i].b;
    }
    qsort(items, n, sizeof(Item), cmp);

    for (int i = 0; i < k; i++) ans += items[i].a;
    for (int i = k; i < n; i++) ans += (items[i].a <= items[i].b ? items[i].a : items[i].b);

    printf("%d\n", ans);
    return 0;
}