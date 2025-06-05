#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> sizes(n + 1); 
    map<int, set<int>> available; 

    for (int i = 1; i <= n; ++i) {
        cin >> sizes[i];
        available[sizes[i]].insert(i);
    }

    while (m--) {
        int type;
        cin >> type;

        if (type == 1) {
            int car_size;
            string pref;
            cin >> car_size >> pref;

            auto it = available.lower_bound(car_size); 
            if (it == available.end()) {
                cout << -1 << '\n';
            } else {
                int pos = -1;
                if (!it->second.empty()) {
                    if (pref == "small") {
                        pos = *it->second.begin();
                    } else {
                        pos = *it->second.rbegin();
                    }
                    cout << pos << '\n';
                    it->second.erase(pos);
                    if (it->second.empty()) {
                        available.erase(it);
                    }
                } else {
                    cout << -1 << '\n';
                }
            }
        }
        else if (type == 2) {
            int y;
            cin >> y;
            if (y >= 1 && y <= n) {
                int sz = sizes[y];
                available[sz].insert(y);
            }
        }
        else if (type == 3) {
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