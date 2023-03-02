#include "LongComplex.h"

const LongComplex LongComplex::czero = LongComplex("0");
const LongComplex LongComplex::cinf = LongComplex(LongNumber(cringe("inf")), LongNumber(cringe("inf")));
const LongComplex LongComplex::I = LongComplex("i");
const LongComplex LongComplex::cnan = LongComplex(LongNumber(cringe("nan")), LongNumber(cringe("nan")));
const LongComplex LongComplex::half = LongComplex("0.5");
const LongComplex LongComplex::one = LongComplex("1");

bool can_change(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return false;
    return true;
}

void not_num_converter(LongComplex &num) {
    if (iscnan(num))
        num = LongComplex::cnan;
    else if (iscinf(num))
        num = LongComplex::cinf;
}

LongComplex::LongComplex(const LongNumber &real_, const LongNumber &imag_) {
    this->real = real_;
    this->imag = imag_;
    not_num_converter(*this);
}

LongComplex::LongComplex(const LongComplex &num) {
    this->real = num.real;
    this->imag = num.imag;
}

LongComplex::LongComplex(std::string s) {
    if (!correct_complex_num(s)) {
        throw std::logic_error("Incorrect complex number form");
    }
    if (s.empty()) {
        this->real = LongNumber::zero;
        this->imag = LongNumber::zero;
        return;
    }
    std::string real_{}, imag_{};
    unsigned long long start_pos = 0, imag_pos = s.size();
    if (s[0] == '-') {
        real_ += s[0];
        ++start_pos;
    }
    for (unsigned long long i = start_pos; i < s.size(); ++i) {
        if (s[i] == '+' or s[i] == '-') {
            if (s[i] == '-')
                imag_ += s[i];
            imag_pos = i + 1;
            break;
        } else if (s[i] == 'i' and i == s.size() - 1) {
            if (i == start_pos) {
                real_ += "1";
            }
            imag_ = real_;
            real_.clear();
            break;
        }
        real_ += s[i];
    }
    for (unsigned long long i = imag_pos; i < s.size(); ++i) {
        if (s[i] == 'i' and i == s.size() - 1) {
            if (i == imag_pos)
                imag_ += "1";
            break;
        }
        imag_ += s[i];
    }
    this->real = LongNumber(real_);
    this->imag = LongNumber(imag_);
    not_num_converter(*this);
}

LongComplex &LongComplex::operator=(const LongComplex &rhs) = default;

LongComplex LongComplex::operator+(const LongComplex &rhs) const {
    if (iscnan(*this) or iscnan(rhs))
        return LongComplex::cnan;
    else if (iscinf(*this) or iscinf(rhs))
        return LongComplex::cinf;
    return LongComplex{this->real + rhs.real, this->imag + rhs.imag};
}

LongComplex LongComplex::operator-(const LongComplex &rhs) const {
    if (iscnan(*this) or iscnan(rhs) or (iscinf(*this) and iscinf(rhs)))
        return LongComplex::cnan;
    else if (iscinf(*this) or iscinf(rhs))
        return LongComplex::cinf;
    return LongComplex{this->real - rhs.real, this->imag - rhs.imag};
}

LongComplex LongComplex::operator*(const LongComplex &rhs) const {
    if (iscnan(*this) or iscnan(rhs) or (iscinf(*this) and rhs == LongComplex::czero) or (iscinf(rhs) and *this == LongComplex::czero))
        return LongComplex::cnan;
    else if (iscinf(*this) or iscinf(rhs))
        return LongComplex::cinf;
    return LongComplex{this->real * rhs.real - this->imag * rhs.imag,
                       this->imag * rhs.real + this->real * rhs.imag};
}

LongComplex LongComplex::operator/(const LongComplex &rhs) const {
    if (iscnan(*this) or iscnan(rhs) or (iscinf(*this) and iscinf(rhs)) or (*this == LongComplex::czero and rhs == LongComplex::czero))
        return LongComplex::cnan;
    else if (iscinf(*this) or rhs == LongComplex::czero)
        return LongComplex::cinf;
    else if (*this == LongComplex::czero or iscinf(rhs))
        return LongComplex::czero;
    return LongComplex{(this->real * rhs.real + this->imag * rhs.imag) / (rhs.real * rhs.real + rhs.imag * rhs.imag),
                       (this->imag * rhs.real - this->real * rhs.imag) / (rhs.real * rhs.real + rhs.imag * rhs.imag)};
}

bool operator==(const LongComplex &lhs, const LongComplex &rhs) {
    return lhs.real == rhs.real and lhs.imag == rhs.imag;
}

bool operator!=(const LongComplex &lhs, const LongComplex &rhs) {
    return !(lhs == rhs);
}

LongComplex &LongComplex::operator+=(const LongComplex &rhs) {
    *this = *this + rhs;
    return *this;
}

LongComplex &LongComplex::operator-=(const LongComplex &rhs) {
    *this = *this - rhs;
    return *this;
}

LongComplex &LongComplex::operator*=(const LongComplex &rhs) {
    *this = *this * rhs;
    return *this;
}

LongComplex &LongComplex::operator/=(const LongComplex &rhs) {
    *this = *this / rhs;
    return *this;
}

LongComplex LongComplex::operator-() const {
    if (can_change(*this)) {
        LongComplex tmp = *this;
        tmp.real = -this->real;
        tmp.imag = -this->imag;
        return tmp;
    }
    return *this;
}

bool correct_complex_num(const std::string &num) {
    if (num.empty())
        return true;
    if (num[0] == '+')
        return false;
    std::string real_, imag_;
    unsigned long long imag_pos = num.size(), start_pos = 0;
    if (num[0] == '-') {
        real_ += '-';
        start_pos = 1;
    }
    for (unsigned long long i = start_pos; i < num.size(); ++i) {
        if (num[i] == '-') {
            imag_ += '-';
            imag_pos = i + 1;
            break;
        } else if (num[i] == '+') {
            if (i == num.size() - 1 or num[i + 1] == '-') {
                return false;
            }
            imag_pos = i + 1;
            break;
        } else if (num[i] == 'i' and i == num.size() - 1) {
            break;
        }
        real_ += num[i];
    }
    for (unsigned long long i = imag_pos; i < num.size(); ++i) {
        if (i == num.size() - 1) {
            if (num[i] == 'i')
                break;
            else
                return false;
        }
        imag_ += num[i];
    }
    return correct_long_num(real_) and correct_long_num(imag_);
}

std::ostream &operator<<(std::ostream &out, const LongComplex &num) {
    out << num.to_string();
    return out;
}

std::istream &operator>>(std::istream &in, LongComplex &num) {
    std::string s_num;
    in >> s_num;
    if (correct_complex_num(s_num)) {
        num = LongComplex(s_num);
    } else {
        num = LongComplex::czero;
    }
    return in;
}

bool iscnan(const LongComplex &num) {
    return num.get_real() == LongNumber::nan or num.get_imag() == LongNumber::nan;
}

bool iscinf(const LongComplex &num) {
    return abs(num.get_real()) == LongNumber::inf or abs(num.get_imag()) == LongNumber::inf;
}

std::string LongComplex::to_string() const {
    if (iscnan(*this))
        return "NaN";
    else if (iscinf(*this))
        return "cinf";
    std::string tmp;
    tmp += this->real.to_string() + (this->imag.sign ? "" : "+") + this->imag.to_string() + "*i";
    return tmp;
}

void LongComplex::set_real(const LongNumber &real_) {
    if (can_change(*this)) {
        this->real = real_;
        not_num_converter(*this);
        return;
    }
    throw std::logic_error("Can't change non-numerical value");
}

void LongComplex::set_imag(const LongNumber &imag_) {
    if (can_change(*this)) {
        this->imag = imag_;
        not_num_converter(*this);
        return;
    }
    throw std::logic_error("Can't change non-numerical value");
}

LongNumber LongComplex::get_real() const {
    return this->real;
}

LongNumber LongComplex::get_imag() const {
    return this->imag;
}

LongNumber abs(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongNumber::nan;
    return sqrt(num.get_real() * num.get_real() + num.get_imag() * num.get_imag());
}

LongNumber phase(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongNumber::nan;
    return atan(num.get_imag() / num.get_real());
}

LongComplex exp(const LongComplex &num) {
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::cinf;
    LongNumber e_a = exp(num.get_real());
    return LongComplex{e_a * cos(num.get_imag()), e_a * sin(num.get_imag())};
}

LongComplex ln(const LongComplex &num) {
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num) or num == LongComplex::czero)
        return LongComplex::cinf;
    return LongComplex{ln(abs(num)), num.get_real() < LongNumber::zero ? phase(num) + LongNumber::Pi : phase(num)};
}

LongComplex log(const LongComplex &num, const LongComplex &base) {
    if (iscnan(num) or iscnan(base))
        return LongComplex::cnan;
    return ln(num) / ln(base);
}

LongComplex pow(const LongComplex &num, const LongComplex &deg) {
    if (iscnan(num) or iscnan(deg) or ((num == LongComplex::czero or iscinf(num)) and deg == LongComplex::czero) or (iscinf(deg) and abs(num) == LongNumber::one))
        return LongComplex::cnan;
    else if (iscinf(deg) and (iscinf(num) or abs(num) > LongNumber::one))
        return LongComplex::cinf;
    else if ((iscinf(deg) and abs(num) < LongNumber::one) or num == LongComplex::czero)
        return LongComplex::czero;
    else if (deg.get_imag() == LongNumber::zero and deg.get_real() == floor(deg.get_real())) {
        LongComplex tmp = deg.get_real() >= LongNumber::zero ? num : LongComplex::one / num, tmp1 = tmp;
        for (auto i = LongNumber::one; i < abs(deg.get_real()); ++i) {
            tmp *= tmp1;
        }
        return tmp;
    }
    return exp(ln(num) * deg);
}

LongComplex factorial(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num.get_real() == floor(num.get_real()) and num.get_imag() == LongNumber::zero) {
        if (num.get_real().sign)
            return LongComplex::cinf;
        else
            return (LongComplex) factorial(num.get_real());
    }
    LongComplex num_num = LongComplex(num.get_real() - floor(num.get_real()) + LongNumber::one, num.get_imag()), G_minus = LongComplex(LongNumber::G - LongNumber::half),
            y = num_num + G_minus, la1, la2;
    for (int i = 12; i >= 0; --i) {
        la2 = la2 * num_num + (LongComplex) LongNumber::lanczos_num_coeffs[i];
        la1 = la1 * num_num + (LongComplex) LongNumber::lanczos_den_coeffs[i];
    }
    LongComplex la_rez = la2 / la1, r = la_rez / exp(y);
    r *= pow(y, num_num - LongComplex::half);
    for (auto i = num.get_real(); i >= LongNumber::one; --i) {
        r *= LongComplex(i, num.get_imag());
    }
    for (auto i = num.get_real() + LongNumber::one; i <= LongNumber::one; ++i) {
        r /= LongComplex(i, num.get_imag());
    }
    return r;
}

LongComplex surd(const LongComplex &num, const LongComplex &deg) {
    if (iscnan(num) or iscnan(deg) or deg == LongComplex::czero or (iscinf(deg) and (iscinf(num) or num == LongComplex::czero)))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::cinf;
    else if (num == LongComplex::czero)
        return LongComplex::czero;
    else if (iscinf(deg))
        return LongComplex::one;
    else if (deg == LongComplex::one)
        return num;
    return exp(ln(num) / deg);
}