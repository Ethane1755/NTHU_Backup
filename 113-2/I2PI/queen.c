#include <stdio.h>

int N, ans = 0;
int queen[15]; // queen[i] 表示第 i 行皇后放在第 queen[i] 列

int is_safe(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (queen[i] == col || (row - i) == (col - queen[i]) || (row - i) == (queen[i] - col))
            return 0;
    }
    return 1;
}

void dfs(int row) {
    if (row == N) {
        ans++;
        return;
    }
    for (int col = 0; col < N; col++) {
        if (is_safe(row, col)) {
            queen[row] = col;
            dfs(row + 1);
        }
    }
}

int main() {
    scanf("%d", &N);
    dfs(0);
    printf("%d\n", ans);
    return 0;
}