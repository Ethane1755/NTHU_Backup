#include <stdio.h>
#include <string.h>

int main () {
    int N;
    char str[2001], sub[2001];
    scanf("%d", &N);
    while(N--) {
        int len, cnt = 0;
        scanf("%s", str);
        len = strlen(str);

        for (int center = 0; center < len; center++) {
            int l = center, r = center;
            while (l >= 0 && r < len && str[l] == str[r]) {
                cnt++;
                l--;
                r++;
            }
        }
        for (int center = 0; center < len-1; center++) {
            int l = center, r = center+1;
            while (l >= 0 && r < len && str[l] == str[r]) {
                cnt++;
                l--;
                r++;
            }
        }
        printf("%d\n", cnt);
    }

    return 0;
}