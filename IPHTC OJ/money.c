#include <stdio.h>

int x; int y; int z;

int main () {
    scanf("%d %d %d", &x, &y, &z);
    printf("%d %d %d\n", (x+z-y) / 2, (y+x-z) / 2, (z+y-x) / 2);
    return 0;
}