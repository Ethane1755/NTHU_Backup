#include <stdio.h>

long long int gcd(long long int a, long long int b) {
    if (a < b) {
        long long int temp = a;
        a = b;
        b = temp;
    }
    if (a % b == 0) {
        return b;
    }
    return gcd(b, a%b);
}

int main () {
    int N;
    scanf("%d", &N);
    while (N--) {
        int len = 0;
        long long int list[1001];
        scanf("%d", &len);
        for (int i = 0; i < len; i++) {
            scanf("%lld", &list[i]);
        }
        long long int max_gcd = 0;
        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                long long int g = gcd(list[i], list[j]);
                if (g > max_gcd) max_gcd = g;
            }
        }
        printf("%lld\n", max_gcd);
    }
    return 0;
}