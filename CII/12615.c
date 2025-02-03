#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define TARGET "ICPCASIASG"
#define TARGET_LEN 10

// 騎士的 8 種移動方式
const int knight_moves[8][2] = {
    {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, 
    {1, -2}, {1, 2}, {2, -1}, {2, 1}
};

int N;
char chess[MAX_N][MAX_N];

// 深度優先搜尋 (DFS)，檢查是否可以找到目標字串
int dfs(int x, int y, int index) {
    if (index == TARGET_LEN) return 1; // 成功找到完整字串

    for (int i = 0; i < 8; i++) {
        int nx = x + knight_moves[i][0];
        int ny = y + knight_moves[i][1];

        if (nx >= 0 && nx < N && ny >= 0 && ny < N) { // 確保在範圍內
            if (chess[nx][ny] == TARGET[index]) { 
                if (dfs(nx, ny, index + 1)) return 1; // 繼續搜尋
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d", &N);
    
    char S[MAX_N * MAX_N + 1];
    scanf("%s", S);

    // 將 S 轉換為 N×N 的棋盤
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            chess[i][j] = S[i * N + j];
        }
    }

    // 從所有 'I' 開始 DFS
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (chess[i][j] == 'I') {
                if (dfs(i, j, 1)) {
                    printf("YES\n");
                    return 0;
                }
            }
        }
    }

    printf("NO\n");
    return 0;
}
