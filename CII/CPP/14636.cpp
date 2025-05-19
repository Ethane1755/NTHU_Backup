#include <iostream>
#include <vector>
#include <map>
#include <climits>
using namespace std;

int main () {
    int N;
    cin >> N;
    vector<string> names(N);
    vector<int> prices(N);
    for (int i = 0; i < N; ++i) cin >> names[i];
    for (int i = 0; i < N; ++i) cin >> prices[i];

    map<string, vector<int>> drink_prices;
    for (int i = 0; i < N; ++i) {
        drink_prices[names[i]].push_back(prices[i]);
    }

    int Q;
    cin >> Q;
    map<string, int> ans;
    for (int i = 0; i < Q; ++i) {
        string query;
        cin >> query;
        if (ans.count(query)) {
            cout << ans[query] << endl;
            continue;
        }
        const vector<int>& v = drink_prices[query];
        int m = v.size();
        if (m < 3) {
            cout << "0" << endl;
            ans[query] = 0;
            continue;
        }
        // 預處理 prefix max
        vector<int> prefix_max(m, INT_MIN);
        prefix_max[0] = v[0];
        for (int j = 1; j < m; ++j) {
            prefix_max[j] = max(prefix_max[j-1], v[j]);
        }
        // 預處理 suffix max
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