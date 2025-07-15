#include <stdio.h>

int art(int n1, int n2, int n3) {
    if (n3 - n2 == n2 - n1) {
        return n3 - n2;
    } else {
        return 0;
    }
}

int main() {
    int n1, n2, n3;
    scanf(" %d %d %d", &n1, &n2, &n3);
    int k = art(n1, n2, n3);
    if (k) {
        printf("%d %d", n1 - k, n3 + k);
    } else {
        int r = n2 / n1;
        printf("%d %d", n1 / r, n3 * r);
    }
    return 0;
}