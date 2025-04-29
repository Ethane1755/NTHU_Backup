#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAX_X 1000000

char s[MAX_X + 5];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int x;
        scanf("%d", &x);
        scanf("%s", s);

        int real_len = strlen(s); // 實際字串長度
        int len = real_len;       // 模擬長度（可能 > x）

        for (int i = 0; i < x; ++i) {
            int c = s[i] - '0';

            int tail_len = (len - i - 1 + MOD) % MOD;
            long long add = 1LL * tail_len * (c - 1) % MOD;
            len = (len + add) % MOD;

            // 只擴充到 real_len <= x 時才繼續建構字串
            if (real_len < x) {
                int copy_len = real_len - i - 1;
                int total_copy = c - 1;
                while (total_copy-- && real_len < x) {
                    for (int j = 0; j < copy_len && real_len < x; ++j) {
                        s[real_len++] = s[i + 1 + j];
                    }
                }
            }
        }

        printf("%d\n", len);
    }

    return 0;
}