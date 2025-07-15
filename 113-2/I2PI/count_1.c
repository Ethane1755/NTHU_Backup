#include <stdio.h>

int count (int x) {
    int cnt = 0;
    while (x > 0) {
        if (x % 10 == 1) cnt++; // 檢查個位數是否為 1
        x /= 10;
    }
    return cnt;
}

long long int prefix[1000001]; // 預先計算 1 的個數前綴和

int main () {
    // 預先計算前綴和
    for (int i = 1; i <= 1000000; i++) {
        prefix[i] = prefix[i - 1] + count(i);
    }

    int N;
    scanf("%d", &N);
    while (N--) {
        int l, r;
        scanf("%d %d", &l, &r);
        long long int a = prefix[r] - prefix[l - 1]; // 修正區間計算方式
        printf("%lld\n", a);
    }
    return 0;
}