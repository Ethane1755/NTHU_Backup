#include <stdio.h>
#include <string.h>
#define MAXN 5005

int t, n, q;
int L[MAXN], R[MAXN];
int section_guarded[MAXN], solo[MAXN], two_cover[MAXN];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &q);
        for (int i = 0; i < q; ++i) {
            scanf("%d %d", &L[i], &R[i]);
        }

        // 差分計算被覆蓋次數
        memset(section_guarded, 0, sizeof(int) * (n + 2));
        for (int i = 0; i < q; ++i) {
            section_guarded[L[i]]++;
            section_guarded[R[i] + 1]--;
        }
        for (int i = 1; i <= n; ++i) {
            section_guarded[i] += section_guarded[i - 1];
        }

        // total covered
        int total_covered = 0;
        for (int i = 1; i <= n; ++i) {
            if (section_guarded[i] > 0) total_covered++;
        }

        // 每位士兵的 solo 區段數
        memset(solo, 0, sizeof(int) * q);
        for (int i = 0; i < q; ++i) {
            for (int j = L[i]; j <= R[i]; ++j) {
                if (section_guarded[j] == 1) solo[i]++;
            }
        }

        // prefix sum for section_guarded == 2
        two_cover[0] = 0;
        for (int i = 1; i <= n; ++i) {
            two_cover[i] = two_cover[i - 1] + (section_guarded[i] == 2);
        }

        int ans = 0;
        for (int i = 0; i < q; ++i) {
            for (int j = i + 1; j < q; ++j) {
                int commonL = (L[i] > L[j]) ? L[i] : L[j];
                int commonR = (R[i] < R[j]) ? R[i] : R[j];
                int overlap_loss = 0;
                if (commonL <= commonR) {
                    overlap_loss = two_cover[commonR] - two_cover[commonL - 1];
                }
                int loss = solo[i] + solo[j] + overlap_loss;
                int remain = total_covered - loss;
                if (remain > ans) ans = remain;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}