#include <iostream>
#include <set>

using namespace std;

int main () {
    set<int> s = {0, 2, 3};
    auto it = s.lower_bound(2);
    cout << *it << endl;
    return 0;
}