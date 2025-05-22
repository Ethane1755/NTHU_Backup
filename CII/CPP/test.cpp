#include <iostream>
#include <vector>
#include <climits>
#include <map>

using namespace std;

int main () {
    int N, Q;
    cin >> N;
    vector<string> name(N);
    vector<int> price(N);
    for (int i = 0; i < N; i++) cin >> name[i];
    for (int i = 0; i < N; i++) cin >> price[i];

    map<string, vector<int>> name_price;
    for (int i = 0; i < N; i++) {
        name_price[name[i]].push_back(price[i]);
    }

    map<string, int> ans;

    cin >> Q;
    for (int i = 0; i < Q; i++) {
        string query;
        cin >> query;
        if (ans.count(query)) {
            cout << ans[query] << endl;
            continue;
        }

        const vector<int>& v = name_price[query];
        int m = v.size();
        if (m < 3) {
            cout << "0" << endl;
            ans[query] = 0;
            continue;
        }

        vector<int> prefix_max(m, INT_MIN);
        prefix_max[0] = v[0];
        for (int j = 1; j < m; ++j) {
            prefix_max[j] = max(prefix_max[j-1], v[j]);
        }
        vector<int> suffix_max(m, INT_MIN);
        suffix_max[m-1] = v[m-1];
        for (int j = m-2; j >= 0; --j) {
            suffix_max[j] = max(suffix_max[j+1], v[j]);
        }

        int best = INT_MIN;
        for (int j = 1; j < m-1; ++j) {
            int pu = prefix_max[j-1];
            int pv = v[j];
            int pw = suffix_max[j+1];
            best = max(best, pu - pv + pw);
        }
        ans[query] = best;
        cout << best << endl;
    }
    return 0;
}