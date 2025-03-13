#include <stdio.h>

int main() {
    int ab, bc, ac;
    scanf("%d %d %d", &ab, &bc, &ac);
    int a = ((ac - bc) + ab) / 2;
    int b = ((ab - ac) + bc) / 2;
    int c = ((bc - ab) + ac) / 2;
    printf("%d %d %d\n", a, b, c);
    return 0;
}