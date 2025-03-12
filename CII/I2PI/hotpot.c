#include <stdio.h>

int main () {
    int a1, a2, b1, b2, c;
    scanf("%d.%d %d.%d d", &a1, &a2, &b1, &b2, &c);
    int ans1 = a1 * b1 * 10000;
    int ans2 = a2 * b2 + a1 * b2 * 100 + a2 * b1 * 100;
    int a = ans1 + ans2;
    printf("%d.%0d", a / 10000, a % 10000);

    return 0;
}