#include <iostream>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

int x;

set<int> S;

int main () {
    int N, M;
    cin >> N >> M;
    while (N--) {
        int temp;
        cin >> temp;
        S.insert(temp);
    }
    while (M--) {
        cin >> x;
        auto it = S.lower_bound(x);
        int closest;
        if (it == S.end()) {
            closest = *prev(it);
        } else if (it == S.begin()) {
            closest = *it;
        } else {
            int higher = *it;
            int lower = *prev(it);
            if (abs(higher - x) < abs(lower - x)) closest = higher;
            else closest = lower;
        }
        cout << closest << endl;
    }
    return 0;
}