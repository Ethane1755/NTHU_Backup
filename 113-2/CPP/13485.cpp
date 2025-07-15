#include <iostream>
#include <string>
#include "13485.h"

String_Calculator::String_Calculator(const std::string str) : s(str) {}
String_Calculator& String_Calculator::Add(const string adder) {
    this -> s += adder;
    return *this;
}
String_Calculator& String_Calculator::Subtract(const string subber) {
    size_t pos = this -> s.find(subber, 0);
    size_t size = subber.size();
    if (pos == string::npos) this -> s = "error";
    else this -> s.erase(pos, size);
    return *this;
}
String_Calculator& String_Calculator::DividedBy(const string diver) {
    size_t count = 0;
    size_t i = 0;
    size_t len = this -> s.size() - diver.size() + 1;
    for (i; i < len; i++) {
        size_t flag = 0;
        for (size_t j = 0; j < diver.size() && !flag; j++) {
            if (diver[j] != this -> s[i + j]) flag = 1;
        }
        if (!flag) count++;
    }
    this -> s = to_string(count);
    return *this;
}

void String_Calculator::output() const {
    cout << s << '\n';
}

int main(){
    int n;
    string x, y;
    cin >> n;
    while(n--){
        cin >> x >> y;
        String_Calculator a(x), ans;
        ans = a.Subtract(y).Add(y).DividedBy(y);
        ans.output();
    }
}