#include <stdio.h>
#include <string.h>

int cmp(const char *a, const char *b) {
    int la = strlen(a);
    if (la % 2 == 1) {
        return strcmp(a, b) == 0;
    }
    int half = la / 2;
    char a1[501], a2[501], b1[501], b2[501];
    strncpy(a1, a, half); a1[half] = '\0';
    strcpy(a2, a + half);
    strncpy(b1, b, half); b1[half] = '\0';
    strcpy(b2, b + half);

    // Check both possible splits
    if ((cmp(a1, b1) && cmp(a2, b2)) || (cmp(a1, b2) && cmp(a2, b1))) {
        return 1;
    } else {
        return 0;
    }
}

int main () {
    int N;
    char a[1001], b[1001];
    scanf("%d", &N);
    while(N--) {
        scanf("%s", a);
        scanf("%s", b);
        if (cmp(a, b)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

