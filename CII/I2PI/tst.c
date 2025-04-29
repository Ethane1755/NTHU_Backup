#include <stdio.h>
#include <string.h>

#define MOD 1000000007

int main () {
    int N;
    scanf("%d", &N);
    while (N--) {
        int k;
        char lst[501];
        scanf("%d", &k);
        scanf("%s", lst);

        int real_len = strlen(lst);
        int len = real_len;
        for (int i = 0; i < k; i++) {
            int c = lst[i] - '0';
            int tail_len = (len - i - 1 + MOD) % MOD;
            long long add = (1LL * tail_len * (c - 1)) % MOD;
            len = (len + add) % MOD;

            if (real_len < k) {
                int copy_len = real_len - i -1;
                int copy_times = c - 1;
                while (copy_times-- && real_len < k) {
                    for (int j = 0; j < copy_len && real_len < k; j++) {
                        lst[real_len++] = lst[i + 1 + j];
                    }
                }
            }
        }
        printf("%d\n", len);
    }

    return 0;
}