#include <stdio.h>
#define DIFF 'A'-'1' //or 'B'-'2', 'C'-'3', ..., 'I'-'9' 

int main(void)
{
    char input[4];

    scanf("%s", input);
    printf("%c%c%c", input[0]+DIFF, input[1]+DIFF, input[2]+DIFF);

    return 0;
}