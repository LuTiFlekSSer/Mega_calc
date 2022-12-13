#ifndef MEGA_CALCAPP_LONGNUMBER_H
#define MEGA_CALCAPP_LONGNUMBER_H

#include <vector>
#include <string>
#include <type_traits>
#include <iostream>
#include <concepts>

template<typename T>
concept arithmetic = std::is_arithmetic<T>::value;

class LongNumber {
private:
    bool sign = false;
    std::vector<char> numbers;
    long long exp;

public:
    LongNumber();

    LongNumber(const LongNumber &num);

    explicit LongNumber(std::string num);

    template<arithmetic T>
    explicit LongNumber(T num) : LongNumber(std::to_string(num)) {};

    LongNumber &operator=(const LongNumber &rhs);

    LongNumber operator+(const LongNumber &rhs);

    friend std::ostream &operator<<(std::ostream &out, const LongNumber &num);

    friend std::istream &operator>>(std::istream &in, LongNumber &num);

    friend std::strong_ordering operator<=>(const LongNumber &lhs, const LongNumber &rhs);

    friend bool operator!=(const LongNumber &lhs, const LongNumber &rhs);

    friend bool operator==(const LongNumber &lhs, const LongNumber &rhs);

    [[nodiscard]] std::string to_string() const;

    ~LongNumber();
};

bool correct_num(const std::string &num);

#endif
