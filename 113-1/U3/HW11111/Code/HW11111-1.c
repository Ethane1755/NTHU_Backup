#include <stdio.h>

int main(void)
{
    char mapping[10] = {'\0', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    char input[3];

    scanf("%c%c%c", &input[0], &input[1], &input[2]);
    printf("%c%c%c", mapping[(input[0]-'0')], mapping[(input[1]-'0')], mapping[(input[2]-'0')]);

    return 0;
}
