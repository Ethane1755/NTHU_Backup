#include <stdio.h>

int main () {
    int a1, a2, b1, b2;
    scanf("%d.%d %d.%d", &a1, &a2, &b1, &b2);
    int a = a1 * b1 * 10000 + a2 * b2 + a1 * b2 * 100 + a2 * b1 * 100;
    printf("%d.%04d", a / 10000, a % 10000);

    return 0;
}