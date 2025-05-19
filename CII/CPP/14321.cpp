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
            // If no element is greater than or equal to x, take the largest element
            closest = *prev(it);
        } else if (it == S.begin()) {
            // If no element is smaller than x, take the smallest element
            closest = *it;
        } else {
            // Compare the current element and the previous one
            int higher = *it;
            int lower = *prev(it);
            if (abs(higher - x) < abs(lower - x)) closest = higher;
            else if (abs(higher - x) > abs(lower - x)) closest = lower;
            else if (abs(higher - x) == abs(lower - x)) closest = lower;
        }
        cout << closest << endl;
    }
    return 0;
}