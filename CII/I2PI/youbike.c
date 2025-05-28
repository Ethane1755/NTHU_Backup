#include <stdio.h>

#define MAXN 100005

int pos[MAXN];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &pos[i]);
    }

    int last = 0; // last position where bike was changed (or start)
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (pos[i] - last > k) {
            // Can't reach this checkpoint from last change
            if (i == 0 || pos[i] - pos[i-1] > k) {
                printf("The Legend Falls.\n");
                return 0;
            }
            // Change bike at previous checkpoint
            last = pos[i-1];
            cnt++;
            // After changing, check again for current checkpoint
            if (pos[i] - last > k) {
                printf("The Legend Falls.\n");
                return 0;
            }
        }
    }
    printf("%d\n", cnt);
    return 0;
}