#ifndef MEGA_CALCAPP_LONGNUMBER_H
#define MEGA_CALCAPP_LONGNUMBER_H

#include <vector>
#include <string>
#include <type_traits>
#include <iostream>
#include <concepts>
#include "cringe class/cringe.h"

template<typename T>
concept arithmetic = std::is_arithmetic<T>::value;


class LongNumber {
private:
    bool sign = false;
    std::vector<char> numbers;
    long long exp{};

    explicit LongNumber(const cringe &par);

public:
    static const LongNumber zero;
    static const LongNumber Pi;
    static const LongNumber e;
    static const LongNumber nan; //false 10 0
    static const LongNumber inf; //false 11 0
    static const LongNumber infm; //true 11 0

    LongNumber();

    LongNumber(const LongNumber &num);

    explicit LongNumber(std::string num);

    template<arithmetic T>
    explicit LongNumber(T num) : LongNumber(std::to_string(num)) {};

    LongNumber &operator=(const LongNumber &rhs);

    LongNumber operator+(const LongNumber &rhs) const;

    LongNumber operator-(const LongNumber &rhs) const;

    LongNumber operator-() const;

    friend std::ostream &operator<<(std::ostream &out, const LongNumber &num);

    friend std::istream &operator>>(std::istream &in, LongNumber &num);

    friend std::strong_ordering operator<=>(const LongNumber &lhs, const LongNumber &rhs);

    friend bool operator!=(const LongNumber &lhs, const LongNumber &rhs);

    friend bool operator==(const LongNumber &lhs, const LongNumber &rhs);

    [[nodiscard]] std::string to_string() const;

    ~LongNumber();
};

LongNumber abs(const LongNumber &num);

LongNumber max(const LongNumber &num1, const LongNumber &num2);

LongNumber min(const LongNumber &num1, const LongNumber &num2);

bool isnan(const LongNumber &num);

bool isinf(const LongNumber &num);

bool correct_num(const std::string &num);


#endif
