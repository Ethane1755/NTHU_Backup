#include <stdio.h>

int main() {
    int l, r;
    int a1, a2;
    scanf("%d %d", &l, &r);
    for (int i = l; i <= r; i++) {
        for (int j = i + 1; j <= r; j++) {
            if (j % i == 0) {
                a1 = i;
                a2 = j;
                printf("%d %d\n", a1, a2);
                return 0;
            }
        }
    }
}