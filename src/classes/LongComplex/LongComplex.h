#ifndef MEGA_CALCAPP_LONGCOMPLEX_H
#define MEGA_CALCAPP_LONGCOMPLEX_H

#include "../LongNumber/LongNumber.h"
#include "string"

class LongComplex {
public:
    LongNumber real;
    LongNumber imag;
    static const LongComplex czero;
    static const LongComplex cnan;
    static const LongComplex cinf;
    static const LongComplex I;

    LongComplex() : LongComplex(LongNumber::zero, LongNumber::zero) {};

    explicit LongComplex(std::string s);

    template<arithmetic T>
    explicit LongComplex(T num) : LongComplex(LongNumber(num)) {};

    template<arithmetic T, arithmetic Y>
    LongComplex(T real_, Y imag_) : LongComplex(LongNumber(real_), LongNumber(imag_)) {};

    explicit LongComplex(const LongNumber &num) : LongComplex(num, LongNumber::zero) {};

    LongComplex(const LongNumber &real_, const LongNumber &imag_);

    LongComplex(const LongComplex &num);

    LongComplex &operator=(const LongComplex &rhs);

    LongComplex operator+(const LongComplex &rhs) const;

    LongComplex operator-(const LongComplex &rhs) const;

    LongComplex operator*(const LongComplex &rhs) const;

    LongComplex operator/(const LongComplex &rhs) const;

    LongComplex &operator+=(const LongComplex &rhs);

    LongComplex &operator-=(const LongComplex &rhs);

    LongComplex &operator*=(const LongComplex &rhs);

    LongComplex &operator/=(const LongComplex &rhs);

    LongComplex operator-() const;

    [[nodiscard]] std::string to_string() const;

    friend std::ostream &operator<<(std::ostream &out, const LongComplex &num);

    friend std::istream &operator>>(std::istream &in, LongComplex &num);

    friend bool operator==(const LongComplex &lhs, const LongComplex &rhs);

    friend bool operator!=(const LongComplex &lhs, const LongComplex &rhs);

    ~LongComplex() = default;
};

bool iscnan(const LongComplex &num);

bool iscinf(const LongComplex &num);

bool correct_complex_num(const std::string &num);

LongNumber abs(const LongComplex &num);

LongNumber phase(const LongComplex &num);

LongComplex exp(const LongComplex &num);

LongComplex ln(const LongComplex &num);

LongComplex log(const LongComplex &num, const LongComplex &base);

LongComplex pow(const LongComplex &num, const LongComplex &deg);

LongComplex factorial(const LongComplex &num);

#endif
