#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int a, b, c;
}Pair;

int cmp(const void *x, const void *y) {
    Pair *p1 = (Pair*)x;
    Pair *p2 = (Pair*)y;

    if (p1->a > p2->a) return 1;
    if (p1->a < p2->a) return -1;
    if (p1->b > p2->b) return 1;
    if (p1->b < p2->b) return -1;
    return 0;
}

int main() {
    int N;
    scanf("%d", &N);

    Pair arr[N];
    for(int i = 0; i < N; i++) {
        scanf("%d %d", &arr[i].a, &arr[i].b);
        arr[i].c = i;
    }

    qsort(arr, N, sizeof(Pair), cmp);

    for (int i = 0; i < N - 1; i++) {
        printf("%d ", arr[i].c + 1);
    }
    printf("%d\n", arr[N - 1].c + 1);
    return 0;
}