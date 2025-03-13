#include <stdio.h>

int main() {
    int num, N;
    int a[100001];
    int prefix[100001];
    char b[20];
    scanf("%d %d", &num, &N);
    for (int i = 0; i < num; i++) {
        scanf("%d", &a[i]);
        for (int j = 0; j < 14; j++) {
            scanf("%c", &b[j]);
        }
    }
    prefix[0] = 0;
    for (int i = 1; i <= num; i++) {
        prefix[i] = prefix[i - 1] + a[i-1];
        printf("%d ", prefix[i]);
    }
    printf("\n");
    while(N--) {
        int l, r, ans;
        scanf("%d %d", &l, &r);
        //printf("%d %d\n", prefix[r], prefix[l-1]);
        if (l != r) ans = prefix[r] - prefix[l-1];
        else ans = a[l-1];
        printf("%d\n", ans);
    }


    return 0;
}