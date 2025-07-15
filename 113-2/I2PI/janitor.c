#include <stdio.h>

int main () {
    int n, q;
    unsigned long long temp;
    unsigned long long prefix[1000005];
    char trash[15];
    prefix[0] = 0;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%llu", &temp);
        prefix[i] = prefix[i - 1] + temp;
        for (int j = 0; j < 13; j++) {
            scanf("%c", &trash[j]);
        }
    }
    for (int i = 0; i < q; i++) {
        int start, end;
        scanf("%d %d", &start, &end);
        printf("%llu\n", prefix[end] - prefix[start - 1]);
    }

    return 0;
}