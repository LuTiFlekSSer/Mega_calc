#ifndef MEGA_CALCAPP_LONGCOMPLEX_H
#define MEGA_CALCAPP_LONGCOMPLEX_H

#include "../LongNumber/LongNumber.h"
#include "string"

class LongComplex {
private:
    LongNumber real;
    LongNumber imag;

    friend void copy_with_double_round(LongComplex &to_change, const LongComplex &new_num);

    friend void move_with_double_round(LongComplex &to_change, LongComplex &&new_num);

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

    LongComplex(LongComplex &&num) noexcept;

    void set_real(const LongNumber &real_);

    void set_imag(const LongNumber &imag_);

    [[nodiscard]] LongNumber get_real() const;

    [[nodiscard]] LongNumber get_imag() const;

    [[nodiscard]] std::string to_string() const;

    LongComplex &operator=(const LongComplex &rhs);

    LongComplex &operator=(LongComplex &&rhs) noexcept;

    LongComplex operator+(const LongComplex &rhs) const;

    LongComplex operator-(const LongComplex &rhs) const;

    LongComplex operator*(const LongComplex &rhs) const;

    LongComplex operator/(const LongComplex &rhs) const;

    LongComplex &operator+=(const LongComplex &rhs);

    LongComplex &operator-=(const LongComplex &rhs);

    LongComplex &operator*=(const LongComplex &rhs);

    LongComplex &operator/=(const LongComplex &rhs);

    LongComplex operator-() const;

    friend std::ostream &operator<<(std::ostream &out, const LongComplex &num);

    friend std::istream &operator>>(std::istream &in, LongComplex &num);

    friend bool operator==(const LongComplex &lhs, const LongComplex &rhs);

    friend bool operator!=(const LongComplex &lhs, const LongComplex &rhs);

    ~LongComplex() = default;
};

void copy_with_double_round(LongComplex &to_change, const LongComplex &new_num);

void move_with_double_round(LongComplex &to_change, LongComplex &&new_num);

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

LongComplex sqrt(const LongComplex &num);

LongComplex surd(const LongComplex &num, const LongComplex &deg);

LongComplex sin(const LongComplex &num);

LongComplex asin(const LongComplex &num);

LongComplex cos(const LongComplex &num);

LongComplex acos(const LongComplex &num);

LongComplex tan(const LongComplex &num);

LongComplex atan(const LongComplex &num);

LongComplex ctan(const LongComplex &num);

LongComplex actan(const LongComplex &num);

LongComplex sec(const LongComplex &num);

LongComplex asec(const LongComplex &num);

LongComplex cosec(const LongComplex &num);

LongComplex acosec(const LongComplex &num);

LongComplex sinh(const LongComplex &num);

LongComplex asinh(const LongComplex &num);

LongComplex cosh(const LongComplex &num);

LongComplex acosh(const LongComplex &num);

LongComplex tanh(const LongComplex &num);

LongComplex atanh(const LongComplex &num);

LongComplex ctanh(const LongComplex &num);

LongComplex actanh(const LongComplex &num);

LongComplex sech(const LongComplex &num);

LongComplex asech(const LongComplex &num);

LongComplex cosech(const LongComplex &num);

LongComplex acosech(const LongComplex &num);

LongComplex rad_to_grad(const LongComplex &num);

LongComplex grad_to_rad(const LongComplex &num);

LongComplex floor(const LongComplex &num);

LongComplex ceil(const LongComplex &num);

namespace many_value_f {
    LongNumber phase(const LongComplex &num, const LongComplex &n);

    LongComplex ln(const LongComplex &num, const LongComplex &n);

    LongComplex log(const LongComplex &num, const LongComplex &base, const LongComplex &n, const LongComplex &k);

    LongComplex pow(const LongComplex &num, const LongComplex &deg, const LongComplex &n);

    LongComplex surd(const LongComplex &num, const LongComplex &deg, const LongComplex &n);

    LongComplex sqrt(const LongComplex &num, const LongComplex &n);

    LongComplex asin(const LongComplex &num, const LongComplex &n, const LongComplex &k);

    LongComplex acos(const LongComplex &num, const LongComplex &n, const LongComplex &k);

    LongComplex atan(const LongComplex &num, const LongComplex &n, const LongComplex &k);

    LongComplex actan(const LongComplex &num, const LongComplex &n, const LongComplex &k);

    LongComplex asec(const LongComplex &num, const LongComplex &n, const LongComplex &k);

    LongComplex acosec(const LongComplex &num, const LongComplex &n, const LongComplex &k);

    LongComplex asinh(const LongComplex &num, const LongComplex &n, const LongComplex &k);

    LongComplex acosh(const LongComplex &num, const LongComplex &n, const LongComplex &k);

    LongComplex atanh(const LongComplex &num, const LongComplex &n, const LongComplex &k);

    LongComplex actanh(const LongComplex &num, const LongComplex &n, const LongComplex &k);

    LongComplex asech(const LongComplex &num, const LongComplex &n, const LongComplex &k);

    LongComplex acosech(const LongComplex &num, const LongComplex &n, const LongComplex &k);
}

#endif
