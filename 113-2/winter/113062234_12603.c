#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    scanf("%d", &n);

    char directions[n + 1]; // 字符串需要額外空間存 '\0'
    scanf("%s", directions);

    int positions[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &positions[i]);
    }

    int min_time = INT_MAX;
    int collision = 0; // 標記是否有碰撞

    for (int i = 0; i < n - 1; i++) {
        if (directions[i] == 'R' && directions[i + 1] == 'L') {
            int time = (positions[i + 1] - positions[i]) / 2;
            if (time < min_time) {
                min_time = time;
                collision = 1;
            }
        }
    }

    if (collision)
        printf("%d\n", min_time);
    else
        printf("-1\n");

    return 0;
}
