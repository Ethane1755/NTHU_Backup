#include <stdio.h>

int main() {
    int l, r;
    scanf("%d %d", &l, &r);
    for (int i = l; i <= r; i++) {
        for (int j = i + 1; j <= r; j++) {
            if (j % i == 0) {
                printf("%d %d\n", i, j);
                return 0;
            }
        }
    }
}