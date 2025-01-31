#include <stdio.h>

// 遞迴查找 sk[a] 對應的字符
char find(int a, int L) {
    int prevL = (L - 3) / 2; // sk-1 的長度

    if (a == 0) return 'O';
    if (a == prevL + 1) return 'u';
    if (a == L - 1) return 'Q';

    if (a <= prevL) {
        return find(a - 1, prevL);  // 屬於左邊 sk-1
    } else {
        return find(a - prevL - 2, prevL); // 屬於右邊 sk-1
    }
}

int main() {
    int k, l, r;
    
    while(scanf("%d %d %d", &k, &l, &r) != EOF) {
        // 正確計算 sk 的長度
        int L = 3;
        for (int i = 2; i <= k; i++) {
            L = 2 * L + 3;
        }

        // 查找並輸出區間 [l, r]
        for (int i = l; i <= r; i++) {
            printf("%c", find(i, L));
        }
        printf("\n");
    }
    return 0;
}