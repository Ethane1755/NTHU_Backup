#include <vector>
#include <iostream>
#include <set>
#include <string>
using namespace std;

int decode(vector<int> a) {
    int k = 0;
    for (int i = 0; i < a.size(); i++) {
        k += a[i] * (a.size() - i);
    }
    return k;
}

struct cmp {
    bool operator() (const vector<int> &a, const vector<int> &b) {
        return decode(a) < decode(b);
    }
};

set<vector<int>, cmp> S;

void insert() {
    int input;
    vector<int> temp;
    while(true) {
        cin >> input;
        if (!input) break;
        temp.push_back(input);
    }
    int key = decode(temp);
    for (auto it : S) {
        if (decode(it) == key) {
            cout << "exist\n";
            S.erase(it);
            vector<int> ttemp;
            for (auto i = temp.rbegin(); i < temp.rend(); i++) {
                ttemp.push_back(*i);
            }
            temp = ttemp;
            break;
        }
    }
    S.insert(temp);
}

void range_output() {
    int input, pt[2];
    for (int i = 0; i < 2; i++) {
        vector<int> temp;
        while(true) {
            cin >> input;
            if (!input) break;
            temp.push_back(input);
        }
        pt[i] = decode(temp);
    }
    for (auto it : S) {
        int ID = decode(it);
        if (ID >= pt[0] && ID <= pt[1]) {
            for (auto element : it) {
                cout << element << " ";
            }
            cout << "\n";
        }
    }
}

void output() {
    for (auto lines : S) {
        for (auto elements : lines) {
            cout << elements << " ";
        }
        cout << "\n";
    }
}

int main () {
    string s;
    while (cin >> s) {
        if (s == "insert") insert();
        else if (s == "range_out") range_output();
        else if (s == "output") output();
    }
}