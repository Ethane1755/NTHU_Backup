#include <iostream>
#include <vector>
using namespace std;

int sort (string t) {
    int size = t.size();
    vector<char> pre;
    for (int i = 0; i < size; i++) {       
        if (t[i] == '(' || t[i] == '{' || t[i] == '[' || t[i] == '<') {
            pre.push_back(t[i]);
        }
        else if (t[i] == ')' || t[i] == '}' || t[i] == ']' || t[i] == '>') {
            if (pre.empty()) return 1; 
            char last = pre.back();
            if ((t[i] == ')' && last == '(') ||
                (t[i] == '}' && last == '{') ||
                (t[i] == ']' && last == '[') ||
                (t[i] == '>' && last == '<')) {
                pre.pop_back();
            } else {
                return 1; 
            }
        }
    }
    //for (auto it : pre) cout << it << endl;
    if (pre.size() != 0) return 1;
    return 0;  
}

int main () {
    int N;
    string testcase;
    cin >> N;
    cin.ignore();
    for (int i = 0; i < N; i++) {
        getline(cin, testcase);
        int ans = sort(testcase);
        if (ans) cout << "Case " << i + 1 << ": No" << endl;
        else cout << "Case " << i + 1 << ": Yes" << endl;     
    }
    return 0;
}