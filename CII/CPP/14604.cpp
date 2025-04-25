#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include "14604.h"
using namespace std;


Polynomial parsePolynomial(const string& str) {
    stringstream ss;
    ss << str;
    string s;
    char sign;
    int *coeffs = new int[105]();
    int degree = 0;
    while (ss >> s) {
        sign = s[0];
        int num = 0;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == 'x') {
                if (i + 1 < s.size() && s[i + 1] == '^') {
                    int exp = 0;
                    i += 2; // 跳過 '^'
                    while (i < s.size() && isdigit(s[i])) {
                        exp = exp * 10 + (s[i] - '0');
                        i++;
                    }
                    degree = max(degree, exp); 
                    coeffs[exp] += (sign == '+' ? num : -num);
                } else {
                    coeffs[1] += (sign == '+' ? num : -num);
                    degree = max(degree, 1);
                }
                break;
            }
            num = num * 10 + (s[i] - '0');
            if (i == s.size() - 1) {
                coeffs[0] += (sign == '+' ? num : -num);
            }
        }
    }

    Polynomial poly(degree, coeffs);
    delete[] coeffs;  // 創建物件後釋放記憶體
    return poly;
}

Polynomial::Polynomial(int deg, const int *coeffs) {
    degree = deg;
    coefficients = new int[deg + 1];
    for (int i = 0; i <= degree; i++) {
        coefficients[i] = coeffs[i];
    }
}

Polynomial::Polynomial(const Polynomial& other) {
    degree = other.degree;
    coefficients = new int[degree + 1];
    for (int i = 0; i <= degree; i++) {
        coefficients[i] = other.coefficients[i];
    }
}

Polynomial Polynomial::operator+(const Polynomial& other) const {
    int maxDeg = max(degree, other.degree);
    int *newCoeffs = new int[maxDeg + 1]();
    for (int i = 0; i <= maxDeg; ++i) {
        int a = (i <= degree) ? coefficients[i] : 0;
        int b = (i <= other.degree) ? other.coefficients[i] : 0;
        newCoeffs[i] = a + b;
    }
    Polynomial result(maxDeg, newCoeffs);
    delete[] newCoeffs;
    return result;
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    int maxDeg = max(degree, other.degree);
    int *newCoeffs = new int[maxDeg + 1]();
    for (int i = 0; i <= maxDeg; ++i) {
        int a = (i <= degree) ? coefficients[i] : 0;
        int b = (i <= other.degree) ? other.coefficients[i] : 0;
        newCoeffs[i] = a - b;
    }
    Polynomial result(maxDeg, newCoeffs);
    delete[] newCoeffs;
    return result;
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    int maxDeg = degree + other.degree;
    int *newCoeffs = new int[maxDeg + 1]();
    for (int i = 0; i <= degree; i++) {
        for (int j = 0; j <= other.degree; j++) {
            newCoeffs[i + j] += coefficients[i] * other.coefficients[j];
        }
    }
    Polynomial result(maxDeg, newCoeffs);
    delete[] newCoeffs;
    return result;
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this == &other) return *this; // 自我賦值檢查
    delete[] coefficients;             // 釋放舊記憶體
    degree = other.degree;
    coefficients = new int[degree + 1];
    for (int i = 0; i <= degree; i++) {
        coefficients[i] = other.coefficients[i];
    }
    return *this;
}

int Polynomial::evaluate(int x) const {
    const int MOD = 1000000007;
    long long res = 0, powx = 1;
    for (int i = 0; i <= degree; i++) {
        res = (res + coefficients[i] * powx) % MOD;
        powx = (powx * x) % MOD;
    }
    if (res < 0) res += MOD;
    return (int)res;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    for (int i = poly.degree; i >= 0; --i) {
        int c = poly.coefficients[i];
        // Always print sign
        if (c >= 0) os << '+';
        else os << '-';

        int abs_c = std::abs(c);

        if (i == 0) {
            os << abs_c;
        } else if (i == 1) {
            if (abs_c == 1) os << "x";
            else os << abs_c << "x";
        } else {
            if (abs_c == 1) os << "x^" << i;
            else os << abs_c << "x^" << i;
        }
        if (i != 0) os << " ";
    }
    return os;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    map<char, Polynomial> polys;
    
    // 讀取多項式定義
    cin.ignore();  // 忽略第一行後的換行符
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        
        char symbol = line[0];
        size_t eqPos = line.find('=');
        if (eqPos == string::npos) continue;
        
        string right = line.substr(eqPos + 1);
        // 去除前導空格
        right.erase(0, right.find_first_not_of(" "));
        
        if (right.length() == 1 && isalpha(right[0])) {
            // 引用形式 (如 t = f)
            polys[symbol] = Polynomial(polys[right[0]]);
        } else {
            // 表達式形式 (如 f = +2x^2 -3x +1)
            polys[symbol] = parsePolynomial(right);
        }
    }
    // 處理操作
    for (int i = 0; i < m; i++) {
        char func1, func2, op;
        int x;
        cin >> func1 >> op >> func2;
        cin >> x;
        Polynomial f1 = polys[func1];
        Polynomial f2 = polys[func2];
        Polynomial result;

        if (op == '+')
            result = f1 + f2;
        else if (op == '-')
            result = f1 - f2;
        else if (op == '*')
            result = f1 * f2;

        cout << result << " = " << result.evaluate(x) << endl;
    }
    
    return 0;
}