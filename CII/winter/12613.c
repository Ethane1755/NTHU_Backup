#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long int a, b;
        scanf("%lld %lld", &a, &b);
        long long int cnt = 0;
        long long b1 = 9;
        while(b1 <= b) {
            cnt += a;
            b1 = 10 * b1 + 9;
        }
        printf("%lld\n", cnt);
    }

    return 0;
}