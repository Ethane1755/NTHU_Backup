#include <stdio.h>

long long int sc(int k) {
    if (k == 0) {
        return 0;
    } else {
        return 8 * sc(k - 1) + 1;
    }
}

int main() {
    int num;
    scanf("%d", &num);
    printf("%lld\n",sc(num));
    return 0;
}
