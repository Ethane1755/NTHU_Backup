#include <iostream>
#include <vector>
#include <iomanip>
#include "14618.h"
using namespace std;

// Scene Constructor: 動態配置 2D grid
Scene::Scene(int n, int m) : row(n), col(m) {
    grid = new int*[row];
    for (int i = 0; i < row; ++i) {
        grid[i] = new int[col];
        for (int j = 0; j < col; ++j) grid[i][j] = 0;
    }
}

// Scene Destructor: 釋放記憶體
Scene::~Scene() {
    for (int i = 0; i < row; ++i) delete[] grid[i];
    delete[] grid;
}

// 更新遊戲狀態到第 m 秒
void Scene::update(int m) {
    gameTimer = m;
}

// 檢查是否有可消除的列
void Scene::checkBlock() {
    bool eliminated;
    do {
        eliminated = false;
        for (int i = row - 1; i >= 0; --i) {
            if (checkRow(i)) {
                eliminate(i);
                eliminated = true;
                break; // 只消一行，然後再檢查
            }
        }
        if (eliminated) update(gameTimer); // 讓所有積木再掉到底
    } while (eliminated);
}

// 判斷第 r 列是否可消除
bool Scene::checkRow(int r) const {
    for (int j = 0; j < col; ++j) {
        if (grid[r][j] == 0) return false;
    }
    return true;
}

// 消除第 r 列，並將上方全部下移
void Scene::eliminate(int r) {
    for (int i = r; i > 0; --i) {
        for (int j = 0; j < col; ++j) {
            grid[i][j] = grid[i-1][j];
        }
    }
    for (int j = 0; j < col; ++j) grid[0][j] = 0;
}

// 輸出遊戲畫面
void Scene::print() const {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j)
            std::cout << std::setw(1) << grid[i][j];
        std::cout << "\n";
    }
}

// 各種 Block 的 draw 實作
// 注意 x, y 為 1-based，grid 為 0-based
// ...existing code...

// 幫助函式：判斷這個 block 形狀在下落 offset 時會不會碰到東西
bool canPlace(int** grid, int row, int col, const vector<pair<int,int>>& shape, int x, int y, int offset) {
    for (auto [dx, dy] : shape) {
        int nx = x + dx + offset;
        int ny = y + dy;
        if (nx < 0 || nx >= row || ny < 0 || ny >= col) return false;
        if (grid[nx][ny] != 0) return false;
    }
    return true;
}

// IBlock: 直條
void IBlock::draw(int**& grid) {
    vector<pair<int,int>> shape = {{0,0},{1,0},{2,0}};
    int offset = 0;
    // 找到能下落的最大 offset
    while (canPlace(grid, 10, 15, shape, x-1, y-1, offset+1)) ++offset;
    for (auto [dx, dy] : shape)
        grid[x-1+dx+offset][y-1+dy] = label;
}

// JBlock
void JBlock::draw(int**& grid) {
    vector<pair<int,int>> shape = {{0,0},{0,1},{1,1},{2,1}};
    int offset = 0;
    while (canPlace(grid, 10, 15, shape, x-1, y-1, offset+1)) ++offset;
    for (auto [dx, dy] : shape)
        grid[x-1+dx+offset][y-1+dy] = label;
}

// LBlock
void LBlock::draw(int**& grid) {
    vector<pair<int,int>> shape = {{0,0},{1,0},{2,0},{2,1}};
    int offset = 0;
    while (canPlace(grid, 10, 15, shape, x-1, y-1, offset+1)) ++offset;
    for (auto [dx, dy] : shape)
        grid[x-1+dx+offset][y-1+dy] = label;
}

// SBlock
void SBlock::draw(int**& grid) {
    vector<pair<int,int>> shape = {{0,1},{0,2},{1,0},{1,1}};
    int offset = 0;
    while (canPlace(grid, 10, 15, shape, x-1, y-1, offset+1)) ++offset;
    for (auto [dx, dy] : shape)
        grid[x-1+dx+offset][y-1+dy] = label;
}

// TBlock
void TBlock::draw(int**& grid) {
    vector<pair<int,int>> shape = {{0,0},{0,1},{0,2},{1,1}};
    int offset = 0;
    while (canPlace(grid, 10, 15, shape, x-1, y-1, offset+1)) ++offset;
    for (auto [dx, dy] : shape)
        grid[x-1+dx+offset][y-1+dy] = label;
}

// OBlock
void OBlock::draw(int**& grid) {
    vector<pair<int,int>> shape = {{0,0}};
    int offset = 0;
    while (canPlace(grid, 10, 15, shape, x-1, y-1, offset+1)) ++offset;
    for (auto [dx, dy] : shape)
        grid[x-1+dx+offset][y-1+dy] = label;
}