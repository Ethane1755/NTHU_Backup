#include <stdio.h>

#define MAXN 200001

int a[MAXN], b[MAXN], pos[MAXN], eaten[MAXN];

int main() {
    int n;
    scanf("%d", &n);

    // 讀取 a[i]，並記錄位置
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        pos[a[i]] = i; // 記錄西瓜的位置
    }

    // 讀取 b[i]
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }

    int lastEatenIndex = -1; // 記錄上次吃到的最深位置

    for (int i = 0; i < n; i++) {
        int index = pos[b[i]]; // 找到 b[i] 在 a 中的位置

        if (index > lastEatenIndex) { // 需要吃掉新的西瓜
            eaten[i] = index - lastEatenIndex;
            lastEatenIndex = index;
        } else { // b[i] 已經被吃過了
            eaten[i] = 0;
        }
    }

    // 輸出結果
    for (int i = 0; i < n - 1; i++) {
        printf("%d ", eaten[i]);
    }
    printf("%d\n", eaten[n - 1]);

    return 0;
}