#ifndef MEGA_CALCAPP_LONGNUMBER_H
#define MEGA_CALCAPP_LONGNUMBER_H

#include <vector>
#include <string>
#include <type_traits>
#include <iostream>
#include <concepts>
#include <cmath>
#include "cringe class/cringe.h"

template<typename T>
concept arithmetic = std::is_arithmetic<T>::value;

template<typename T>
concept numeric = std::is_integral<T>::value;

class LongNumber {
    friend LongNumber factorial(const LongNumber &num);

    friend LongNumber pow(const LongNumber &num1, const LongNumber &num2);

    template<numeric T>
    friend LongNumber pow(const LongNumber &num1, const T &num2);

    friend LongNumber exp(const LongNumber &num);

    friend LongNumber ln(const LongNumber &num);

    friend LongNumber log(const LongNumber &num1, const LongNumber &num2);

    friend LongNumber floor(const LongNumber &num);

    friend LongNumber ceil(const LongNumber &num);

private:
    bool sign = false;
    std::vector<char> numbers;
    long long exp{};

    explicit LongNumber(const cringe &par);

    void round();

public:
    static const LongNumber zero;
    static const LongNumber one;
    static const LongNumber two;
    static const LongNumber e;
    static const LongNumber Pi;
    static const LongNumber nan; //false 10 0
    static const LongNumber inf; //false 11 0
    static const LongNumber infm; //true 11 0
    static const LongNumber eps;

    LongNumber();

    LongNumber(const LongNumber &num);

    explicit LongNumber(std::string num);

    template<arithmetic T>
    explicit LongNumber(T num) : LongNumber(num == std::floor(num) ? std::to_string((long long) num) : std::to_string(num)) {};

    LongNumber &operator=(const LongNumber &rhs);

    LongNumber operator+(const LongNumber &rhs) const;

    LongNumber operator-(const LongNumber &rhs) const;

    LongNumber operator*(const LongNumber &rhs) const;

    LongNumber operator/(const LongNumber &rhs) const;

    LongNumber &operator++();

    LongNumber operator++(int);

    LongNumber &operator--();

    LongNumber operator--(int);

    LongNumber &operator+=(const LongNumber &rhs);

    LongNumber &operator-=(const LongNumber &rhs);

    LongNumber &operator*=(const LongNumber &rhs);

    LongNumber &operator/=(const LongNumber &rhs);

    LongNumber operator-() const;

    [[nodiscard]] LongNumber inv() const;

    friend std::ostream &operator<<(std::ostream &out, const LongNumber &num);

    friend std::istream &operator>>(std::istream &in, LongNumber &num);

    friend std::strong_ordering operator<=>(const LongNumber &lhs, const LongNumber &rhs);

    friend bool operator!=(const LongNumber &lhs, const LongNumber &rhs);

    friend bool operator==(const LongNumber &lhs, const LongNumber &rhs);

    [[nodiscard]] std::string to_string() const;

    ~LongNumber();
};

bool isnan(const LongNumber &num);

bool isinf(const LongNumber &num);

bool isinfm(const LongNumber &num);

bool correct_num(const std::string &num);

LongNumber abs(const LongNumber &num);

LongNumber max(const LongNumber &num1, const LongNumber &num2);

LongNumber exp(const LongNumber &num);

LongNumber ln(const LongNumber &num);

LongNumber log(const LongNumber &num1, const LongNumber &num2);

LongNumber min(const LongNumber &num1, const LongNumber &num2);

LongNumber floor(const LongNumber &num);

LongNumber ceil(const LongNumber &num);

LongNumber factorial(const LongNumber &num);

LongNumber pow(const LongNumber &num1, const LongNumber &num2);

template<numeric T>
LongNumber pow(const LongNumber &num1, const T &num2) {
    if (isnan(num1) or (num1 == LongNumber::zero and num2 == 0) or ((isinf(num1) or isinfm(num1)) and num2 == 0))
        return LongNumber::nan;
    else if (num2 == 0)
        return LongNumber(1);
    else if (num1 == LongNumber::zero)
        return LongNumber::zero;
    LongNumber tmp1 = num2 < 0 ? num1.inv() : num1, tmp2 = tmp1;
    tmp1.round();
    for (auto i = 1; i < std::abs(num2); ++i) {
        tmp2 *= tmp1;
        tmp2.round();
    }
    return tmp2;
}

#endif
