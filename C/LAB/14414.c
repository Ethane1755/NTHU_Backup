#include <stdio.h>
#include <ctype.h>

int main() {
    char a;
    char s[21];
    int battalion, company, group, remainder = 0;

    // Read input
    scanf("%c %s", &a, s);

    // Determine and print military branch
    if (isupper(a)) {
        printf("Army\n");
    } else {
        printf("Navy\n");
    }

    // Extract and print Battalion (first 3 digits as an integer)
    sscanf(s, "%3d", &battalion);
    printf("%d\n", battalion);

    // Extract and print Company (4th to 8th digits as an integer)
    sscanf(s + 3, "%5d", &company);
    printf("%d\n", company);

    // Extract and print Platoon (16th digit, mapping 1->A, 2->B, ...)
    int platoon_digit = s[15] - '0';
    printf("%c\n", 'A' + platoon_digit - 1);

    // Calculate the Group as (ID % 4) + 1
    for (int i = 0; i < 20; i++) {
        remainder = (remainder * 10 + (s[i] - '0')) % 4;
    }
    group = remainder + 1;
    printf("%d\n", group);

    return 0;
}