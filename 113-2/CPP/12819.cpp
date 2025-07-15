#include <iostream>                  // 載入輸入輸出函式庫
#include <vector>                    // 載入向量容器
#include <queue>                     // 載入佇列（優先佇列）
#include <unordered_set>             // 載入無序集合（hash set）
#include <unordered_map>
#include <algorithm>                 // 載入常用演算法
using namespace std;                 // 使用標準命名空間

// 目標狀態
const vector<int> goal = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0}; // 15-puzzle 的完成狀態

// 狀態壓成一維方便hash
struct State {
    vector<int> board;               // 棋盤狀態（一維陣列）
    int g, h, zero_pos;              // g: 目前步數, h: 預估剩餘步數, zero_pos: 0 的位置
    bool operator>(const State& o) const { return g + h > o.g + o.h; } // 比較函式（A*用）
};

// hash function for unordered_set
struct VectorHash {
    size_t operator()(const vector<int>& v) const {
        size_t h = 0;
        for (int x : v) h = h * 31 + x; // 簡單 hash 計算
        return h;
    }
};

// 曼哈頓距離 + Linear Conflict
int heuristic(const vector<int>& board) {
    int dist = 0;
    // 曼哈頓距離
    for (int i = 0; i < 16; ++i) {
        if (board[i] == 0) continue; // 跳過空格
        int val = board[i] - 1;
        dist += abs(i / 4 - val / 4) + abs(i % 4 - val % 4); // 計算每個數字到目標位置的距離
    }
    // Linear Conflict（簡單版，只考慮行）
    for (int row = 0; row < 4; ++row) {
        for (int i = 0; i < 4; ++i) {
            int idx1 = row * 4 + i;
            int t1 = board[idx1];
            if (t1 == 0 || (t1 - 1) / 4 != row) continue; // 只考慮在正確行的數字
            for (int j = i + 1; j < 4; ++j) {
                int idx2 = row * 4 + j;
                int t2 = board[idx2];
                if (t2 == 0 || (t2 - 1) / 4 != row) continue;
                if (t1 > t2) dist += 2; // 若有衝突，加 2
            }
        }
    }
    // 列的 linear conflict 也可加上
    for (int col = 0; col < 4; ++col) {
        for (int i = 0; i < 4; ++i) {
            int idx1 = i * 4 + col;
            int t1 = board[idx1];
            if (t1 == 0 || (t1 - 1) % 4 != col) continue; // 只考慮在正確列的數字
            for (int j = i + 1; j < 4; ++j) {
                int idx2 = j * 4 + col;
                int t2 = board[idx2];
                if (t2 == 0 || (t2 - 1) % 4 != col) continue;
                if (t1 > t2) dist += 2; // 若有衝突，加 2
            }
        }
    }
    return dist; // 回傳總估算距離
}

// A* 搜尋演算法
int Astar(const vector<vector<int>>& puzzle) {
    vector<int> start;
    int zero_pos = 0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            start.push_back(puzzle[i][j]);
            if (puzzle[i][j] == 0) zero_pos = i * 4 + j;
        }
    priority_queue<State, vector<State>, greater<State>> pq;
    unordered_map<vector<int>, int, VectorHash> visited; // 狀態 -> 最小步數
    pq.push({start, 0, heuristic(start), zero_pos});
    visited[start] = 0;

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    while (!pq.empty()) {
        State cur = pq.top(); pq.pop();
        if (cur.board == goal) return cur.g;
        int x = cur.zero_pos / 4, y = cur.zero_pos % 4;
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) continue;
            int npos = nx * 4 + ny;
            vector<int> next = cur.board;
            swap(next[cur.zero_pos], next[npos]);
            if (visited.count(next) && visited[next] <= cur.g + 1) continue;
            visited[next] = cur.g + 1;
            pq.push({next, cur.g + 1, heuristic(next), npos});
        }
    }
    return -1;
}

int main () {
    vector<vector<int>> puzzle(4, vector<int>(4)); // 宣告 4x4 棋盤
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cin >> puzzle[i][j];                  // 讀入棋盤
    if (puzzle == vector<vector<int>>{{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}}) {
        cout << 0 << endl;
        return 0;
    }
    cout << Astar(puzzle) << endl;                // 輸出最少步數
    return 0;
}