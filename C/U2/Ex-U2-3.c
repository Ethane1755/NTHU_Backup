#include <stdio.h>

int main(void)
{
    int x = 16;

    printf("decimal: %d, hexadecimal: %x\n", x, x);
    printf("decimal: %d, hexadecimal: %#x\n", x, x);

    return 0;
}
