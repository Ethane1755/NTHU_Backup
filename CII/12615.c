#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define TARGET "ICPCASIASG"
#define TARGET_LEN 10

const int knight_moves[8][2] = {
    {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, 
    {1, -2}, {1, 2}, {2, -1}, {2, 1}
};

int N;
char chess[MAX_N][MAX_N];

int dfs(int x, int y, int index) {
    if (index == TARGET_LEN) return 1; 

    for (int i = 0; i < 8; i++) {
        int nx = x + knight_moves[i][0];
        int ny = y + knight_moves[i][1];

        if (nx >= 0 && nx < N && ny >= 0 && ny < N) { 
            if (chess[nx][ny] == TARGET[index]) { 
                if (dfs(nx, ny, index + 1)) return 1; 
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d", &N);
    
    char S[MAX_N * MAX_N + 1];
    scanf("%s", S);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            chess[i][j] = S[i * N + j];
        }
    }

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
