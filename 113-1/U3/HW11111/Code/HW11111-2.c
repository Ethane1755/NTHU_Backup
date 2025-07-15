#include <stdio.h>

int main(void)
{
    char mapping[10] = {'\0', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    char input[4];

    scanf("%s", input);
    printf("%c%c%c", mapping[(input[0]-'0')], mapping[(input[1]-'0')], mapping[(input[2]-'0')]);

    return 0;
}
