// polynomial.h
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Polynomial {
private:
    int degree;     // 多項式的最高次項
    int symbol;
    int *coefficients;  // 係數數組

public:
    // 構造和析構函數
    Polynomial();  // 預設構造函數
    Polynomial(int deg, const int *coeffs);  // TODO
    Polynomial(const Polynomial& other); // TODO
    ~Polynomial();  // 析構函數

    // 運算符重載
    Polynomial operator+(const Polynomial& other) const;  // TODO
    Polynomial operator-(const Polynomial& other) const;  // TODO
    Polynomial operator*(const Polynomial& other) const;  // TODO
    Polynomial& operator=(const Polynomial& other);  // TODO

    // 多項式操作
    int evaluate(int x) const;  // 在x處求值 TODO

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);  // TODO
};

// 預設構造函數（已實現）
inline Polynomial::Polynomial() : degree(0), coefficients(new int[1]) {
    coefficients[0] = 0.0;
}

inline Polynomial::~Polynomial() {
    delete[] coefficients;
}

#endif // POLYNOMIAL_H
