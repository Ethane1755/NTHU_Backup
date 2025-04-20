#include <stdio.h>

unsigned long long int fast_power(unsigned long long int x, unsigned long long int y, unsigned long long int m) {
    unsigned long long int res = 1;
    if (m == 1) return 0;
    x = x % m;
    while (y > 0) {
        if (y % 2 == 1) {
            res = (res * x) % m;
        }
        x = (x * x) % m;
        y /= 2;
    }
    return res;
}

int main () {
    unsigned long long int x, y, m, ans;
    scanf("%llu %llu %llu", &x, &y, &m);
    ans = fast_power(x, y, m);
    printf("%llu\n", ans);
    return 0;
}