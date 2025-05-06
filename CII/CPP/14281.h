#ifndef _FUNC_H
#define _FUNC_H
#include <iostream>
#include <string>
#include <sstream>

class Codec {
public:
    Codec(std::string s): encoded{false}, code_str{s} { }
    virtual ~Codec() { } // virtual destructor; do nothing
    virtual void encode() = 0;
    virtual void decode() = 0;
    void show(std::ostream& os) const {
        os << code_str;
    }
    bool is_encoded() const { return encoded; }
protected:
    bool encoded;
    std::string code_str;
};

class DummyCodec: public Codec {
public:
    DummyCodec(std::string s): Codec(s) { }
    void encode() override { encoded = true; }
    void decode() override { encoded = false; }
};

class RleCodec: public Codec {
    public:
        RleCodec(std::string s): Codec(s) { }
        void encode() override { 
            if (encoded) return;
            std::stringstream ss;
            int n = code_str.size();
            for (int i = 0; i < n;) {
                int j = i;
                while (j < n && code_str[j] == code_str[i]) j++;
                int cnt = j - i;
                if (cnt >= 3) {
                    ss << cnt << code_str[i];
                } else {
                    ss << code_str.substr(i, cnt);
                }
                i = j;
            }
            code_str = ss.str();
            encoded = true;
        }
        void decode() override { 
            if (!encoded) return;
            std::stringstream ss;
            int n = code_str.size();
            for (int i = 0; i < n;) {
                if (isdigit(code_str[i])) {
                    int j = i;
                    while (j < n && isdigit(code_str[j])) j++;
                    int cnt = std::stoi(code_str.substr(i, j - i));
                    if (j < n) {
                        ss << std::string(cnt, code_str[j]);
                        i = j + 1;
                    } else {
                        break;
                    }
                }
                else {
                    ss << code_str[i];
                    i++;
                }
            }
            code_str = ss.str();
            encoded = false;
        }
    };

Codec* getCodec(const std::string& type, const std::string& is) {
    if (type == "Dummy") {
        return new DummyCodec(is);
    } else if (type == "RLE") {
        return new RleCodec(is);
    }
    return nullptr;
}

#endif
