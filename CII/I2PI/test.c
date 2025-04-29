#include <stdio.h>

int N, cnt = 0;
int table[15];

int safe(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (col == table[i] || (col - table[i]) == (row - i) || (col - table[i]) == (i - row)) return 0;
    }
    return 1;
}

void dfs(int row) {
    if (row == N) {
        cnt++;
        return;
    }
    for (int i = 0; i < N; i++) {
        if (safe(row, i)) {
            table[row] = i;
            dfs(row + 1);
        }
    }
}

int main () {
    scanf("%d", &N);
    dfs(0);
    printf("%d\n", cnt);
    return 0;
}