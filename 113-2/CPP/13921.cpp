#include <iostream>
#include <set>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    set<long long> points;

    while (N--) {
        int type;
        long long x;
        cin >> type >> x;
        if (type == 1) {
            // Toggle point x
            if (points.count(x)) points.erase(x);
            else points.insert(x);
        } else {
            // Query segment containing x
            if (points.empty()) {
                cout << -1 << '\n';
                continue;
            }
            auto it = points.lower_bound(x);
            long long left, right;
            if (it == points.begin()) {
                left = LLONG_MIN;
                right = *it;
            } else if (it == points.end()) {
                left = *prev(it);
                right = LLONG_MAX;
            } else {
                left = *prev(it);
                right = *it;
            }
            // If x is at a point, it's on the right segment
            if (x == right) {
                left = right;
                it = points.upper_bound(x);
                if (it == points.end()) right = LLONG_MAX;
                else right = *it;
            }
            if (left == LLONG_MIN || right == LLONG_MAX) cout << -1 << '\n';
            else cout << right - left << '\n';
        }
    }
    return 0;
}