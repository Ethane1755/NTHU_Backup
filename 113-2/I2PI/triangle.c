#include <stdio.h>
#include <string.h>

#define MAXN 100005

long long sum_count[2 * MAXN];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int A, B, C, D;
        scanf("%d %d %d %d", &A, &B, &C, &D);

        // Reset sum_count
        memset(sum_count, 0, sizeof(sum_count));

        // Count how many (x, y) pairs sum to s
        for (int x = A; x <= B; ++x) {
            // y in [B, C]
            int s_min = x + B;
            int s_max = x + C;
            sum_count[s_min]++;
            sum_count[s_max + 1]--;
        }

        // Prefix sum to accumulate counts
        for (int i = 1; i < 2 * MAXN; ++i)
            sum_count[i] += sum_count[i - 1];

        // Now compute the answer
        long long ans = 0;
        for (int s = A + B; s <= B + C; ++s) {
            // valid z ∈ [C, min(D, s-1)]
            int z_low = C;
            int z_high = s - 1;
            if (z_high < z_low) continue;
            if (z_high > D) z_high = D;
            int z_count = z_high - z_low + 1;
            if (z_count > 0)
                ans += (long long)sum_count[s] * z_count;
        }

        printf("%lld\n", ans);
    }

    return 0;
}