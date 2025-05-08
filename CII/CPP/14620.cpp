#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <climits>
using namespace std;

int T, R, C;
vector<string> grid;

struct Position {
    int x, y;
    int operator-(const Position& other) const {
        // TODO-01: 
        // Return the Manhattan distance between two coordinates (i.e., the sum of the differences of their x and y coordinates).
        int dis = abs(x - other.x) + abs(y - other.y);
        return dis;
    }
};

class Entity {
    public:
        Entity(Position pos): pos(pos) {}
        virtual ~Entity() = default;
        virtual void move() = 0;
        Position getPosition() const { return pos; }
    protected:
        Position pos;
};

class Pacman : public Entity {
    public:
        Pacman(Position pos): Entity(pos) {}

        void setGhostPos(const Position& pos) { 
            ghostPosition = pos;
        }
        void move() override {
            int gx = ghostPosition.x, gy = ghostPosition.y;
            static const int dxs[5] = {-1, 1, 0, 0, 0};
            static const int dys[5] = {0, 0, -1, 1, 0};
        
            vector<vector<int>> dist(R, vector<int>(C, -1));
            vector<vector<Position>> prev(R, vector<Position>(C, {-1, -1}));
            queue<Position> q;
            q.push(pos);
            dist[pos.x][pos.y] = 0;
        
            Position target = pos;
            int minStep = INT_MAX;
        
            while (!q.empty()) {
                Position cur = q.front(); q.pop();
                // 如果是豆子且比目前找到的更近
                if (grid[cur.x][cur.y] == 'O' && dist[cur.x][cur.y] < minStep) {
                    minStep = dist[cur.x][cur.y];
                    target = cur;
                }
                for (int d = 0; d < 5; ++d) {
                    int nx = cur.x + dxs[d], ny = cur.y + dys[d];
                    if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
                    if (grid[nx][ny] == '#') continue;
                    if (dist[nx][ny] != -1) continue;
                    // 避開鬼和鬼的鄰近格
                    if ((abs(nx - gx) + abs(ny - gy)) <= 1) continue;
                    dist[nx][ny] = dist[cur.x][cur.y] + 1;
                    prev[nx][ny] = cur;
                    q.push({nx, ny});
                }
            }
        
            // 若有可達豆子，回推第一步
            if (target.x != pos.x || target.y != pos.y) {
                Position cur = target;
                while (!(prev[cur.x][cur.y].x == pos.x && prev[cur.x][cur.y].y == pos.y)) {
                    cur = prev[cur.x][cur.y];
                }
                pos = cur;
                return;
            }
        
            // 否則離鬼最遠
            int best = pos - ghostPosition;
            Position chosen = pos;
            for (int d = 0; d < 5; d++) {
                int nx = pos.x + dxs[d], ny = pos.y + dys[d];
                if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
                if (grid[nx][ny] == '#') continue;
                int d2 = abs(nx - gx) + abs(ny - gy);
                if (d2 > best) {
                    best = d2;
                    chosen = {nx, ny};
                }
            }
            pos = chosen;
        }
    private:
        // TODO (optional):
        // You can add some extra code here.
        Position ghostPosition;
};

class Ghost : public Entity {
    public:
        Ghost(Position pos): Entity(pos){}

        void setPacmanPos(const Position& pos) {
            pacmanPosition = pos;
        }

        void move() override {
            vector<Position> nbrs;
            static const int dxs[4] = {-1, 1, 0, 0};
            static const int dys[4] = {0, 0, -1, 1};
            for (int i = 0; i < 4; i++) {
                int nx = pos.x + dxs[i];
                int ny = pos.y + dys[i];
                if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
                if (grid[nx][ny] == '#') continue;
                nbrs.push_back({nx, ny});
            }
            if (nbrs.empty()) return;

            Position chosen = pos;
            if (!nbrs.empty()) {
                double p = (double)rand() / RAND_MAX;
                if (p < 0.5) {
                    int best = INT_MAX;
                    for (Position& c : nbrs) {
                        int d = c - pacmanPosition;
                        if (d < best) {
                            best = d;
                            chosen = c;
                        }
                    }
                } else {
                    int idx = rand() % nbrs.size();
                    chosen = nbrs[idx];
                }
            }
            pos = chosen;
        }
    private:
        Position pacmanPosition;
};

ostream& operator<<(ostream& os, const Position& p) {
    os << p.x << ' ' << p.y;
    return os;
}

ostream& operator<<(ostream& os, const Entity& e) {
    os << e.getPosition();
    return os;
}

// TODO (optional):
// You can add some extra code here.

class GameMap {
    public:
        GameMap(const vector<string>& g) {
            // TODO-03:
            // Store the dots from the map.
            for (int i = 0; i < R; i++) {
                for (int j = 0; j < C; j++) {
                    if (g[i][j] == 'O') {
                        dot[i][j] = 1;
                    }
                }
            }
        }
        void eatDot(const Position& p) {
            // TODO-04:
            // Make Pacman eat the dot at his current position (if there is one).
            if (dot[p.x][p.y]) {
                grid[p.x][p.y] = '.';
                dot[p.x][p.y] = 0;
            }
        }
    private:
        int dot[20][20] = {};
};

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> T >> R >> C;
    grid.resize(R);
    for (int i=0; i<R; i++) cin >> grid[i];
    Position pacman_start, ghost_start;
    for (int i=0; i<R; i++) for (int j=0; j<C; j++) {
        if (grid[i][j]=='P') pacman_start = {i,j};
        if (grid[i][j]=='G') ghost_start = {i,j};
    }

    unsigned GHOST_SEED = 48763 ;
    // Choose any integer you like as a random seed! It will affect how the ghosts move.
    // Note: make sure the number you pick fits within the range of an unsigned integer (0 to 4,294,967,295),
    // or unexpected results may happen.

    srand((unsigned)GHOST_SEED);

    GameMap gameMap(grid);
    Pacman pacman(pacman_start);
    Ghost ghost(ghost_start);

    for (int t=0; t<T; t++) {
        pacman.setGhostPos(ghost.getPosition());
        pacman.move();
        gameMap.eatDot(pacman.getPosition());
        ghost.setPacmanPos(pacman.getPosition());
        ghost.move();
        cout << pacman << ' ' << ghost << '\n';
    }
    cout << GHOST_SEED <<'\n';
    return 0;
}