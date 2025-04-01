#include <iostream>
#include "13485.h"

String_Calculator::String_Calculator(const std::string str) : s(str) {}

String_Calculator& String_Calculator::Add(const string add) {
    this->s += add;
    return *this;
}

String_Calculator& String_Calculator::Subtract(const string sub) {
    size_t pos = this->s.find(sub, 0);
    if (pos == string::npos) this->s = "error";
    else this->s.erase(pos, sub.size());
    return *this;
}

String_Calculator& String_Calculator::DividedBy(const string div) {
    size_t div_len = div.size();
    size_t len = this->s.size() - div_len + 1;
    int count = 0;
    for (size_t i = 0; i < len; i++) {
        int flag = 0;
        for (size_t j = 0; j < div_len && !flag; j++) {
            if (div[j] != this->s[i + j]) flag = 1;
        }
        if (!flag) count++;
    }
    this->s = to_string(count);
    return *this;
}

void String_Calculator::output() const {
    cout << s << '\n';
}

// Utin
