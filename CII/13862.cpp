#include <bits/stdc++.h>
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

Person* Person::getRelative(string* arr, int now, int len) {
    Person* cur = this;
    for (int i = now; i < len; ++i) {
        if (arr[i] == "ParentA") {
            if (!cur->ParentA) cur->ParentA = new Person();
            cur = cur->ParentA;
        } else if (arr[i] == "ParentB") {
            if (!cur->ParentB) cur->ParentB = new Person();
            cur = cur->ParentB;
        } else if (arr[i] == "Mate") {
            if (!cur->Mate) cur->Mate = new Person();
            cur = cur->Mate;
        } else if (arr[i] == "Child") {
            if (cur->Children.empty()) {
                Person* child = new Person();
                child->ParentA = cur;
                if (cur->Mate) {
                    child->ParentB = cur->Mate;
                    cur->Mate->Children.push_back(child);
                }
                cur->Children.push_back(child);
            }
            cur = cur->Children[0]; // 假設只取第一個小孩
        }
    }
    return cur;
}

void Person::describe(string* arr, int now, int len) {
    Person* target = getRelative(arr, now, len - 2);
    string attr = arr[len - 2], value = arr[len - 1];

    if (attr == "Name") {
        target->name = value;
    } else if (attr == "Age") {
        target->age = stoi(value);
    } else if (attr == "Gender") {
        target->gender = (value == "MALE") ? MALE : FEMALE;
    } else if (attr == "Personality") {
        if (!target->personality.empty()) target->personality += " ";
        target->personality += value;
    }
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
