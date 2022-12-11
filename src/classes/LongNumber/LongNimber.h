#ifndef MEGA_CALCAPP_LONGNIMBER_H
#define MEGA_CALCAPP_LONGNIMBER_H

#include "vector"
#include "string"
#include <type_traits>
#include "iostream"

class LongNumber {
private:
    bool sign;
    std::vector<char> numbers;
    long long exp;
public:
    LongNumber();

    LongNumber(const LongNumber &num);

    explicit LongNumber(std::string num);

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    explicit LongNumber(T num):LongNumber(std::to_string(num)) {};

    LongNumber &operator=(const LongNumber &rhs);

    std::string to_string();

    ~LongNumber();
};

bool correct_num(const std::string &num);

#endif
