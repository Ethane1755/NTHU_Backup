#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main() {
    int n, m, type, x;
    cin >> n >> m;
    vector<int> space(n + 1);
    map<int, set<int>> available;
    for (int i = 1; i <= n; i++) {
        cin >> space[i];
        available[space[i]].insert(i);
    }
    string instruction;
    while (m--) {
        cin >> type;
        if (type == 1) {
            cin >> x >> instruction;
            auto it = available.lower_bound(x);
            if (it == available.end()) {
                cout << -1 << "\n";
            } else {
                int pos = -1;
                if (!it -> second.empty()) {
                    if (instruction == "small") {
                        pos = *it -> second.begin();
                    } else {
                        pos = *it -> second.rbegin();
                    }
                    cout << pos << "\n";
                    it -> second.erase(pos);
                    if (it -> second.empty()) {
                        available.erase(it);
                    }
                } else {
                    cout << -1 << "\n";
                }
            }
            
        } else if (type == 2) {
            int y;
            cin >> y;
            if (y >= 1 && y <= n) {
                int sz = space[y];
                available[sz].insert(y);
            }
        } else if (type == 3) {
            int z;
            cin >> z;
            if (available.count(z)) {
                cout << available[z].size() << '\n';
            } else {
                cout << 0 << '\n';
            }
        }
    }
    return 0;
}