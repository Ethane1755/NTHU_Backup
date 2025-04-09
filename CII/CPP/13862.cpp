#include<bits/stdc++.h>
#include "13862.h"
using namespace std;

string* ParseStatement(string statement) { // return the parsed array
    stringstream ss;
    vector<string> v;
    ss << statement;
    while (ss >> statement) v.push_back(statement);
    string* ret = new string[v.size()];
    for (int _ = 0; _ < v.size(); ++_) {
        ret[_] = v[_];
    }
    return ret;
}

int getParseStatementLength(string statement) {
    stringstream ss;
    ss << statement;
    int ret = 0;
    while (ss >> statement) ++ret;
    return ret;
}

Person* Person::getRelative (string* arr, int now, int len){
    Person* cur = this;
    for (int i = now; i < len; i++) {
        if (arr[i] == 'ParentA') {
            if (cur -> parentA == nullptr) {
                cur -> parentA = new Person();
                cur -> parentA -> child = cur;
                if (cur -> parentB) {
                    cur -> parentB -> mate = cur -> parentA;
                    cur -> parentA -> mate = cur -> parentB;
                }
            }
            else cur = cur -> parentA;
        } else if (arr[i] == 'ParentB') {
            if (cur -> parentB == nullptr) {
                cur -> parentB = new Person();
                cur -> parentB -> child = cur;
                if (cur -> parentA) {
                    cur -> parentB -> mate = cur -> parentA;
                    cur -> parentA -> mate = cur -> parentB;
                }
            }
            else cur = cur -> parentB;
        } else if (arr[i] == 'Mate') {
            if (cur -> mate) {
                cur = cur -> mate;
            }
            else {
                cur -> mate = new Person();
                cur -> mate -> mate = cur;
                if (cur -> child) {
                    if (cur -> child -> parentA == cur) cur -> child -> parentB = cur -> mate;
                    else cur -> child -> parentA = cur -> mate;
                    cur -> mate -> child = cur -> child;
                }
            }
        } else if (arr[i] == 'Child') {
            if (cur -> child == nullptr) {
                cur -> child = new Person();
                cur -> child -> parentA = cur;
                if (cur -> mate) {
                    cur -> mate -> child = cur -> child;
                    cur -> child -> parentB = cur -> mate;
                }
            }
            else cur = cur -> child;
        }
    }
    return cur;
}

int main () {
    Person* narrator = new Person();

    narrator->name = "Pineapple Senpai";
    narrator->age = 21;
    narrator->gender = MALE;
    narrator->personality = "seasick";

    int Q;
    cin >> Q;
    for (int _ = 0; _ < Q; ++_) {
        // input type of the query
        int type;
        cin >> type;
        // get the parsed array
        string statement;
        getline(cin, statement);
        string* arr = ParseStatement(statement);
        // compute the length of the array
        int len = getParseStatementLength(statement);
        switch(type) {
            case 1: 
                narrator = narrator->getRelative(arr, 0, len);
                break;
            case 2: 
                narrator->describe(arr, 0, len);
                break;
            case 3:
                cout << narrator->info() << "\n";
                break;
        }
        delete[] arr;
    }
    return 0;
}
