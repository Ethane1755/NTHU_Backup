#include <iostream>
#include <list>
#include <queue>
using namespace std;

int main() {
    int n, x;
    string cmd;
    list<int> q; // 主隊伍
    queue<list<int>::iterator> Q[3]; // 各國家最後一人

    cin >> n;
    while (n--) {
        cin >> cmd;
        if (cmd == "ENQUEUE") {
            cin >> x;
            int c = x % 3;
            if (Q[c].empty()) {
                q.push_back(x);
                auto it = prev(q.end());
                Q[c].push(it);
            } else {
                auto it = Q[c].back();
                auto newit = q.insert(next(it), x);
                Q[c].push(newit);
            }
        } else {
            int front = q.front();
            cout << front << endl;
            int c = front % 3;
            if (!Q[c].empty() && *Q[c].front() == front)
                Q[c].pop();
            q.pop_front();
        }
    }
    return 0;
}