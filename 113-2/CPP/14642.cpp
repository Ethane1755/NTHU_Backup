#include <bits/stdc++.h>
using namespace std;

int T, N, M;
vector<string> grid;

struct Position {
    int x, y;

    bool operator<(const Position& other) const {
        return (x != other.x) ? (x < other.x) : (y < other.y);
    }

    int operator-(const Position& other) const {
        vector<vector<bool>> visited(N, vector<bool>(M, false));
        queue<pair<Position,int>> q;
        visited[x][y] = true;
        q.push({ *this, 0 });

        static const int dx[4] = { -1, 1, 0, 0 };
        static const int dy[4] = { 0, 0, -1, 1 };

        while (!q.empty()) {
            auto [cur, dist] = q.front();
            q.pop();
            if (cur.x == other.x && cur.y == other.y) {
                return dist;
            }
            for (int i = 0; i < 4; i++) {
                Position nxt = cur;
                nxt.x = (nxt.x + dx[i] + N) % N;
                nxt.y = (nxt.y + dy[i] + M) % M;
                if (!visited[nxt.x][nxt.y] && grid[nxt.x][nxt.y] != '#') {
                    visited[nxt.x][nxt.y] = true;
                    q.push({ nxt, dist + 1 });
                }
            }
        }
        return INT_MAX;
    }

    void fixedPos() {
        x = (x + N) % N;
        y = (y + M) % M;
    }
};

set<Position> dots;

class Entity {
    public:
        Entity(Position pos): pos(pos) {}
        virtual ~Entity() = default;
        virtual void move() = 0;
        Position getPosition() const { 
            return pos;
        }
        void fixedPos() {
            pos.fixedPos();
        }
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
            struct Candidate {
                Position p;
                int ghostDist;
                int dotDist;
            };

            vector<Candidate> cands;
            static const int dx[4] = { -1, 1, 0, 0 };
            static const int dy[4] = { 0, 0, -1, 1 };

            {
                Position stay = pos;
                int gdist = stay - ghostPosition;
                int ddist = INT_MAX;
                if (!dots.empty()) {
                    vector<vector<bool>> vis(N, vector<bool>(M, false));
                    queue<pair<Position,int>> qq;
                    vis[stay.x][stay.y] = true;
                    qq.push({ stay, 0 });
                    while (!qq.empty()) {
                        auto [cur, d] = qq.front(); qq.pop();
                        if (dots.count(cur)) {
                            ddist = d;
                            break;
                        }
                        for (int i = 0; i < 4; i++) {
                            Position nxt = cur;
                            nxt.x = (nxt.x + dx[i] + N) % N;
                            nxt.y = (nxt.y + dy[i] + M) % M;
                            if (!vis[nxt.x][nxt.y] && grid[nxt.x][nxt.y] != '#') {
                                vis[nxt.x][nxt.y] = true;
                                qq.push({ nxt, d + 1 });
                            }
                        }
                    }
                } else {
                    ddist = 0;
                }
                cands.push_back({ stay, gdist, ddist });
            }

            for (int i = 0; i < 4; i++) {
                Position nxt = pos;
                nxt.x += dx[i];
                nxt.y += dy[i];
                nxt.fixedPos();
                if (grid[nxt.x][nxt.y] == '#') continue;
                int gdist = nxt - ghostPosition;
                int ddist = INT_MAX;
                if (!dots.empty()) {
                    vector<vector<bool>> vis(N, vector<bool>(M, false));
                    queue<pair<Position,int>> qq;
                    vis[nxt.x][nxt.y] = true;
                    qq.push({ nxt, 0 });
                    while (!qq.empty()) {
                        auto [cur, d] = qq.front(); qq.pop();
                        if (dots.count(cur)) {
                            ddist = d;
                            break;
                        }
                        for (int k = 0; k < 4; k++) {
                            Position nn = cur;
                            nn.x = (nn.x + dx[k] + N) % N;
                            nn.y = (nn.y + dy[k] + M) % M;
                            if (!vis[nn.x][nn.y] && grid[nn.x][nn.y] != '#') {
                                vis[nn.x][nn.y] = true;
                                qq.push({ nn, d + 1 });
                            }
                        }
                    }
                } else {
                    ddist = 0;
                }
                cands.push_back({ nxt, gdist, ddist });
            }
            vector<Candidate> safeC, unsafeC;
            for (auto &c : cands) {
                if (c.ghostDist > 1) safeC.push_back(c);
                else unsafeC.push_back(c);
            }

            Position best = pos;
            if (!safeC.empty()) {
                int bestDot = INT_MAX;
                for (auto &c : safeC) {
                    if (c.dotDist < bestDot) {
                        bestDot = c.dotDist;
                        best = c.p;
                    }
                }
            } else {
                int bestGhost = -1;
                int bestDot = INT_MAX;
                for (auto &c : unsafeC) {
                    if (c.ghostDist > bestGhost || (c.ghostDist == bestGhost && c.dotDist < bestDot)) {
                        bestGhost = c.ghostDist;
                        bestDot = c.dotDist;
                        best = c.p;
                    }
                }
            }
            pos = best;
        }
    private:
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
                Position nbr = pos;
                nbr.x += dxs[i];
                nbr.y += dys[i];
                nbr.fixedPos();
                if (grid[nbr.x][nbr.y] != '#') {
                    nbrs.push_back(nbr);
                }
            }
            int now_dis = INT_MAX;
            Position chosen = pos;
            double p = (double)rand() / RAND_MAX;
            if (p < 0.9) {
                if (!nbrs.empty()) {
                    for (Position& c : nbrs) {
                        int d = c - pacmanPosition;
                        if (d <= now_dis) {
                            chosen = c;
                            now_dis = d;
                        }
                    }
                }
            } else {
                int idx = rand() % nbrs.size();
                chosen = nbrs[idx];
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

class GameMap {
    public:
        GameMap(const vector<string>& g) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if (grid[i][j] == 'O'){
                        dots.insert({i, j});
                    }
                }
            }
        }
        void eatDot(const Position& p) {
            if (dots.find(p) != dots.end()) {
                dots.erase(p);
            }
        }
};

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin >> T >> N >> M;
    grid.resize(N);
    for (int i=0;i<N;i++) cin >> grid[i];
    Position pacman_start, ghost_start;
    for (int i=0;i<N;i++) for (int j=0;j<M;j++) {
        if (grid[i][j]=='P') pacman_start = {i,j};
        if (grid[i][j]=='G') ghost_start = {i,j};
    }

    unsigned GHOST_SEED = 712345;
    srand((unsigned)GHOST_SEED);

    GameMap gameMap(grid);
    Pacman pacman(pacman_start);
    Ghost ghost(ghost_start);
    
    for (int t=0; t<T; t++) {
        pacman.setGhostPos(ghost.getPosition());
        pacman.move();
        pacman.fixedPos();
        gameMap.eatDot(pacman.getPosition());
        ghost.setPacmanPos(pacman.getPosition());
        ghost.move();
        ghost.fixedPos();
        cout << pacman << ' ' << ghost << '\n';
    }
    cout << GHOST_SEED << '\n';
    return 0;
} 