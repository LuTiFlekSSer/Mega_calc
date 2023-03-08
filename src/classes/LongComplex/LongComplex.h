#ifndef MEGA_CALCAPP_LONGCOMPLEX_H
#define MEGA_CALCAPP_LONGCOMPLEX_H

#include "../LongNumber/LongNumber.h"
#include "string"

class LongComplex {
private:
    LongNumber real;
    LongNumber imag;
public:
    static const LongComplex czero;
    static const LongComplex cnan;
    static const LongComplex cinf;
    static const LongComplex I;
    static const LongComplex half;
    static const LongComplex one;
    static const LongComplex two;
    static const LongComplex two_I;
    static const LongComplex e;
    static const LongComplex Pi;
    static const LongComplex half_Pi;

    LongComplex() : LongComplex(LongNumber::zero, LongNumber::zero) {};

    explicit LongComplex(std::string s);

    template<arithmetic T>
    explicit LongComplex(T num) : LongComplex(LongNumber(num)) {};

    template<arithmetic T, arithmetic Y>
    LongComplex(T real_, Y imag_) : LongComplex(LongNumber(real_), LongNumber(imag_)) {};

    explicit LongComplex(const LongNumber &num) : LongComplex(num, LongNumber::zero) {};

    LongComplex(const LongNumber &real_, const LongNumber &imag_);

    LongComplex(const LongComplex &num);

    void set_real(const LongNumber &real_);

    void set_imag(const LongNumber &imag_);

    [[nodiscard]] LongNumber get_real() const;

    [[nodiscard]] LongNumber get_imag() const;

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

LongComplex ln(const LongComplex &num);// periodic

LongComplex log(const LongComplex &num, const LongComplex &base);// periodic

LongComplex pow(const LongComplex &num, const LongComplex &deg);// periodic

LongComplex factorial(const LongComplex &num);

LongComplex sqrt(const LongComplex &num);

LongComplex surd(const LongComplex &num, const LongComplex &deg);// periodic

LongComplex sin(const LongComplex &num);// periodic

LongComplex asin(const LongComplex &num);// periodic

LongComplex cos(const LongComplex &num);// periodic

LongComplex acos(const LongComplex &num);// periodic

LongComplex tan(const LongComplex &num);// periodic

LongComplex atan(const LongComplex &num);// periodic

LongComplex ctan(const LongComplex &num);// periodic

LongComplex actan(const LongComplex &num);// periodic

LongComplex sec(const LongComplex &num);// periodic

LongComplex asec(const LongComplex &num);// periodic

LongComplex cosec(const LongComplex &num);// periodic

LongComplex acosec(const LongComplex &num);// periodic

LongComplex sinh(const LongComplex &num);// periodic

LongComplex asinh(const LongComplex &num);// periodic

LongComplex cosh(const LongComplex &num);// periodic

LongComplex acosh(const LongComplex &num);// periodic

LongComplex tanh(const LongComplex &num);// periodic

LongComplex atanh(const LongComplex &num);// periodic

LongComplex ctanh(const LongComplex &num);// periodic

LongComplex actanh(const LongComplex &num);// periodic

LongComplex sech(const LongComplex &num);// periodic

LongComplex asech(const LongComplex &num);// periodic

LongComplex cosech(const LongComplex &num);// periodic

LongComplex acosech(const LongComplex &num);// periodic

#endif
