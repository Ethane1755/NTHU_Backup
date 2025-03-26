#include <stdio.h>

int main () {
    int T, n;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        int temp = 0;
        int unique = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &temp);
            unique = temp ^= unique;
        }
        printf("%d\n", unique);
    }
    return 0;
}
