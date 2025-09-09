#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, N, M, Q, L, R;
    cin >> n;
    while (n--) {
        cin >> N >> M >> Q;
        vector<vector<int>> arr(N, vector<int>(M));
        vector<vector<int>> visited(N, vector<int>(M, 0));
        int* prefix = (int*) malloc (sizeof (int) * N * M);
        int ind = 1;
        prefix[0] = 0;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> arr[i][j];
            }      
        }
    
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        int x = 0, y = 0, dir = 0;

        for (int step = 0; step < N * M; step++) {
            prefix[ind] = prefix[ind - 1] + arr[x][y];
            ind++;
            visited[x][y] = 1;
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (nx >= 0 && nx < N && ny >= 0 && ny < M && !visited[nx][ny]) {
                x = nx;
                y = ny;
            } else {
                dir = (dir + 1) % 4;
                x += dx[dir];
                y += dy[dir];
            }
        }

        while (Q--) {
            cin >> L >> R;
            int ans = prefix[R] - prefix[L - 1];
            cout << ans << endl;
        }
        free(prefix);
    }
    
}