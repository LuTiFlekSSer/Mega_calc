#include "LongComplex.h"
#include "future"

const LongComplex LongComplex::czero = LongComplex("0");
const LongComplex LongComplex::cinf = LongComplex(LongNumber(cringe("inf")), LongNumber(cringe("inf")));
const LongComplex LongComplex::I = LongComplex("i");
const LongComplex LongComplex::cnan = LongComplex(LongNumber(cringe("nan")), LongNumber(cringe("nan")));
const LongComplex LongComplex::half = LongComplex("0.5");
const LongComplex LongComplex::one = LongComplex("1");
const LongComplex LongComplex::two = LongComplex("2");
const LongComplex LongComplex::two_I = LongComplex("2i");
const LongComplex LongComplex::e = LongComplex(LongNumber::e);
const LongComplex LongComplex::Pi = LongComplex(LongNumber::Pi);
const LongComplex LongComplex::half_Pi = LongComplex(LongNumber::Pi * LongNumber::half);

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
    tmp += this->real.to_string() + (this->imag.sign ? "" : "+") + this->imag.to_string() + "i";
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

LongComplex::LongComplex(LongComplex &&num) noexcept {
    real = std::move(num.real);
    imag = std::move(num.imag);
}

LongComplex &LongComplex::operator=(LongComplex &&rhs) noexcept {
    if (this == &rhs)
        return *this;
    real = std::move(rhs.real);
    imag = std::move(rhs.imag);
    return *this;
}

void copy_with_double_round(LongComplex &to_change, const LongComplex &new_num) {
    copy_with_double_round(to_change.real, new_num.real);
    copy_with_double_round(to_change.imag, new_num.imag);
}

void move_with_double_round(LongComplex &to_change, LongComplex &&new_num) {
    move_with_double_round(to_change.real, std::move(new_num.real));
    move_with_double_round(to_change.imag, std::move(new_num.imag));
}

LongNumber abs(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongNumber::nan;
    if (num == LongComplex::czero)
        return LongNumber::zero;
    else if (num.get_real() == LongNumber::zero)
        return abs(num.get_imag());
    else if (num.get_imag() == LongNumber::zero)
        return abs(num.get_real());
    return sqrt(num.get_real() * num.get_real() + num.get_imag() * num.get_imag());
}

LongNumber phase(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongNumber::nan;
    return atan(num.get_imag() / num.get_real()) + (num.get_real() < LongNumber::zero ? (num.get_imag() >= LongNumber::zero ? LongNumber::Pi : -LongNumber::Pi) : LongNumber::zero);
}

LongComplex exp(const LongComplex &num) {
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::cinf;
    auto e_a = std::async(std::launch::async, [&num] { return exp(num.get_real()); }),
            sin_num = std::async(std::launch::async, [&num] { return sin(num.get_imag()); }),
            cos_num = std::async(std::launch::async, [&num] { return cos(num.get_imag()); });
    LongNumber tmp_e_a = e_a.get();
    return LongComplex{tmp_e_a * cos_num.get(), tmp_e_a * sin_num.get()};
}

LongComplex ln(const LongComplex &num) {
    if (iscnan(num) or num == LongComplex::czero)
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::cinf;
    auto ln_num = std::async(std::launch::async, [&num] { return ln(abs(num)); }),
            phase_num = std::async(std::launch::async, [&num] { return phase(num); });
    return LongComplex{ln_num.get(), phase_num.get()};
}

LongComplex log(const LongComplex &num, const LongComplex &base) {
    if (iscnan(num) or iscnan(base))
        return LongComplex::cnan;
    auto ln_num = std::async(std::launch::async, [&num] { return ln(num); }),
            ln_base = std::async(std::launch::async, [&base] { return ln(base); });
    return ln_num.get() / ln_base.get();
}

LongComplex pow(const LongComplex &num, const LongComplex &deg) {
    if (iscnan(num) or iscnan(deg) or ((num == LongComplex::czero or iscinf(num)) and deg == LongComplex::czero) or (iscinf(deg) and abs(num) == LongNumber::one))
        return LongComplex::cnan;
    else if (iscinf(deg) and (iscinf(num) or abs(num) > LongNumber::one))
        return LongComplex::cinf;
    else if ((iscinf(deg) and abs(num) < LongNumber::one) or num == LongComplex::czero)
        return LongComplex::czero;
    else if (deg == LongComplex::czero)
        return LongComplex::one;
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
    auto pow_for_r = std::async(std::launch::async, [&y, &num_num] { return pow(y, num_num - LongComplex::half); }),
            exp_y = std::async(std::launch::async, [&y] { return exp(y); });
    for (int i = 12; i >= 0; --i) {
        la2 = la2 * num_num + (LongComplex) LongNumber::lanczos_num_coeffs[i];
        la1 = la1 * num_num + (LongComplex) LongNumber::lanczos_den_coeffs[i];
    }
    LongComplex la_rez = la2 / la1, r = la_rez / exp_y.get();
    r *= pow_for_r.get();
    for (auto i = num.get_real(); i >= LongNumber::one; --i) {
        r *= LongComplex(i, num.get_imag());
    }
    for (auto i = num.get_real() + LongNumber::one; i <= LongNumber::one; ++i) {
        r /= LongComplex(i, num.get_imag());
    }
    return r;
}

LongComplex sin(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::czero;
    auto exp_1 = std::async(std::launch::async, [&num] { return exp(LongComplex::I * num); }),
            exp_2 = std::async(std::launch::async, [&num] { return exp(-LongComplex::I * num); });
    return (exp_1.get() - exp_2.get()) / (LongComplex::two * LongComplex::I);
}

LongComplex asin(const LongComplex &num) {
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::cinf;
    else if (num == LongComplex::czero)
        return LongComplex::czero;
    return -LongComplex::I * ln(LongComplex::I * num + sqrt(LongComplex::one - num * num));
}

LongComplex cos(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::one;
    auto exp_1 = std::async(std::launch::async, [&num] { return exp(LongComplex::I * num); }),
            exp_2 = std::async(std::launch::async, [&num] { return exp(-LongComplex::I * num); });
    return (exp_1.get() + exp_2.get()) / LongComplex::two;
}

LongComplex acos(const LongComplex &num) {
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::cinf;
    else if (num == LongComplex::czero)
        return LongComplex::half_Pi;
    return LongComplex::half_Pi - asin(num);
}

LongComplex tan(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::czero;
    return LongComplex::two_I / (exp(LongComplex::two_I * num) + LongComplex::one) - LongComplex::I;
}

LongComplex atan(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::czero;
    auto ln_1 = std::async(std::launch::async, [&num] { return ln(LongComplex::one - LongComplex::I * num); }),
            ln_2 = std::async(std::launch::async, [&num] { return ln(LongComplex::one + LongComplex::I * num); });
    return LongComplex::half * LongComplex::I * (ln_1.get() - ln_2.get());
}


LongComplex ctan(const LongComplex &num) {
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num) or num == LongComplex::czero)
        return LongComplex::cinf;
    return LongComplex::I + LongComplex::two_I / (exp(LongComplex::two_I * num) - LongComplex::one);
}

LongComplex actan(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::half_Pi;
    auto ln_1 = std::async(std::launch::async, [&num] { return ln((num - LongComplex::I) / num); }),
            ln_2 = std::async(std::launch::async, [&num] { return ln((num + LongComplex::I) / num); });
    return LongComplex::half * LongComplex::I * (ln_1.get() - ln_2.get());
}

LongComplex sec(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::czero;
    return LongComplex::one / cos(num);
}

LongComplex asec(const LongComplex &num) {
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::half_Pi;
    else if (num == LongComplex::czero)
        return LongComplex::cinf;
    return acos(LongComplex::one / num);
}

LongComplex cosec(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::cinf;
    return LongComplex::one / sin(num);
}

LongComplex acosec(const LongComplex &num) {
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::czero;
    else if (num == LongComplex::czero)
        return LongComplex::cinf;
    return asin(LongComplex::one / num);
}

LongComplex sinh(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::czero;
    auto exp_1 = std::async(std::launch::async, [&num] { return exp(num); }),
            exp_2 = std::async(std::launch::async, [&num] { return exp(-num); });
    return (exp_1.get() - exp_2.get()) * LongComplex::half;
}

LongComplex asinh(const LongComplex &num) {
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::cinf;
    else if (num == LongComplex::czero)
        return LongComplex::czero;
    return ln(sqrt(num * num + LongComplex::one) + num);
}

LongComplex cosh(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::one;
    auto exp_1 = std::async(std::launch::async, [&num] { return exp(num); }),
            exp_2 = std::async(std::launch::async, [&num] { return exp(-num); });
    return (exp_1.get() + exp_2.get()) * LongComplex::half;
}

LongComplex acosh(const LongComplex &num) {
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::cinf;
    else if (num == LongComplex::czero)
        return LongComplex::half_Pi * LongComplex::I;
    auto sqrt_1 = std::async(std::launch::async, [&num] { return sqrt(num + LongComplex::one); }),
            sqrt_2 = std::async(std::launch::async, [&num] { return sqrt(num - LongComplex::one); });
    return ln(sqrt_1.get() * sqrt_2.get() + num);
}

LongComplex tanh(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::czero;
    LongComplex exp_two_num = exp(LongComplex::two * num);
    return (exp_two_num - LongComplex::one) / (exp_two_num + LongComplex::one);
}

LongComplex atanh(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::czero;
    auto ln_1 = std::async(std::launch::async, [&num] { return ln(num + LongComplex::one); }),
            ln_2 = std::async(std::launch::async, [&num] { return ln(LongComplex::one - num); });
    return LongComplex::half * (ln_1.get() - ln_2.get());
}

LongComplex ctanh(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::cinf;
    LongComplex exp_two_num = exp(LongComplex::two * num);
    return (exp_two_num + LongComplex::one) / (exp_two_num - LongComplex::one);
}

LongComplex actanh(const LongComplex &num) {
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::czero;
    else if (num == LongComplex::czero)
        return LongComplex::half_Pi * LongComplex::I;
    auto ln_1 = std::async(std::launch::async, [&num] { return ln(LongComplex::one / num + LongComplex::one); }),
            ln_2 = std::async(std::launch::async, [&num] { return ln(LongComplex::one - LongComplex::one / num); });
    return LongComplex::half * (ln_1.get() - ln_2.get());
}

LongComplex sech(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::one;
    return LongComplex::one / cosh(num);
}

LongComplex asech(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::cinf;
    return acosh(LongComplex::one / num);
}

LongComplex cosech(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::cinf;
    return LongComplex::one / sinh(num);
}

LongComplex acosech(const LongComplex &num) {
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::cinf;
    return asinh(LongComplex::one / num);
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

LongComplex sqrt(const LongComplex &num) {
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::cinf;
    else if (num == LongComplex::czero)
        return LongComplex::czero;
    LongNumber tmp_abs = abs(num);
    auto sqrt_1 = std::async(std::launch::async, [&num, &tmp_abs] { return sqrt((num.get_real() + tmp_abs) * LongNumber::half); }),
            sqrt_2 = std::async(std::launch::async,
                                [&num, &tmp_abs] { return (num.get_imag() >= LongNumber::zero ? LongNumber::one : -LongNumber::one) * sqrt((-num.get_real() + tmp_abs) * LongNumber::half); });
    return LongComplex{sqrt_1.get(), sqrt_2.get()};
}

LongComplex rad_to_grad(const LongComplex &num) {
    if (iscnan(num) or iscinf(num)) {
        return num;
    }
    return num * LongComplex(180) / LongComplex::Pi;
}

LongComplex grad_to_rad(const LongComplex &num) {
    if (iscnan(num) or iscinf(num)) {
        return num;
    }
    return num * LongComplex::Pi / LongComplex(180);
}

LongComplex floor(const LongComplex &num) {
    return LongComplex{floor(num.get_real()), floor(num.get_imag())};
}

LongComplex ceil(const LongComplex &num) {
    return LongComplex{ceil(num.get_real()), ceil(num.get_imag())};
}

LongNumber many_value_f::phase(const LongComplex &num, const LongComplex &n) {
    if (n.get_imag() != LongNumber::zero or n.get_real() != floor(n.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (iscnan(num) or iscinf(num))
        return LongNumber::nan;
    return phase(num) + LongNumber::two_Pi * n.get_real();
}

LongComplex many_value_f::ln(const LongComplex &num, const LongComplex &n) {
    if (n.get_imag() != LongNumber::zero or n.get_real() != floor(n.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (iscnan(num) or num == LongComplex::czero)
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::cinf;
    return ln(num) + LongComplex::I * LongComplex{LongNumber::two_Pi} * LongComplex{n};
}

LongComplex many_value_f::log(const LongComplex &num, const LongComplex &base, const LongComplex &n, const LongComplex &k) {
    if (n.get_imag() != LongNumber::zero or n.get_real() != floor(n.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (k.get_imag() != LongNumber::zero or k.get_real() != floor(k.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (iscnan(num) or iscnan(base))
        return LongComplex::cnan;
    auto ln_num = std::async(std::launch::async, [&num, &n] { return many_value_f::ln(num, n); }),
            ln_base = std::async(std::launch::async, [&base, &k] { return many_value_f::ln(base, k); });
    return ln_num.get() / ln_base.get();
}

LongComplex many_value_f::pow(const LongComplex &num, const LongComplex &deg, const LongComplex &n) {
    if (n.get_imag() != LongNumber::zero or n.get_real() != floor(n.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (iscnan(num) or iscnan(deg) or ((num == LongComplex::czero or iscinf(num)) and deg == LongComplex::czero) or (iscinf(deg) and abs(num) == LongNumber::one))
        return LongComplex::cnan;
    else if (iscinf(deg) and (iscinf(num) or abs(num) > LongNumber::one))
        return LongComplex::cinf;
    else if ((iscinf(deg) and abs(num) < LongNumber::one) or num == LongComplex::czero)
        return LongComplex::czero;
    LongNumber abs_num = abs(num), phase_num = phase(num), N = n.get_real();
    auto pow_r = std::async(std::launch::async, [&abs_num, &deg] { return pow(abs_num, deg.get_real()); }),
            exp_r = std::async(std::launch::async, [&phase_num, &deg, &N] { return exp(-deg.get_imag() * (phase_num + LongNumber::two_Pi * N)); }),
            ln_p = std::async(std::launch::async, [&abs_num] { return ln(abs_num); });
    LongNumber r = pow_r.get() * exp_r.get(), p = ln_p.get() * deg.get_imag() + deg.get_real() * (phase_num + LongNumber::two_Pi * N);
    auto cos_p = std::async(std::launch::async, [&p] { return cos(p); }),
            sin_p = std::async(std::launch::async, [&p] { return sin(p); });
    return LongComplex{r * cos_p.get(), r * sin_p.get()};
}

LongComplex many_value_f::surd(const LongComplex &num, const LongComplex &deg, const LongComplex &n) {
    if (n.get_imag() != LongNumber::zero or n.get_real() != floor(n.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
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
    return pow(num, LongComplex::one / deg, n);
}

LongComplex many_value_f::sqrt(const LongComplex &num, const LongComplex &n) {
    if (n.get_imag() != LongNumber::zero or n.get_real() != floor(n.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::cinf;
    else if (num == LongComplex::czero)
        return LongComplex::czero;
    if (std::stoll(n.get_real().to_string()) % 2 == 0)
        return sqrt(num);
    return -sqrt(num);
}

LongComplex many_value_f::asin(const LongComplex &num, const LongComplex &n, const LongComplex &k) {
    if (n.get_imag() != LongNumber::zero or n.get_real() != floor(n.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (k.get_imag() != LongNumber::zero or k.get_real() != floor(k.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::cinf;
    else if (num == LongComplex::czero)
        return LongComplex::czero;
    return ln(sqrt(num * num + LongComplex::one, k) + num, n);
}

LongComplex many_value_f::acos(const LongComplex &num, const LongComplex &n, const LongComplex &k) {
    if (n.get_imag() != LongNumber::zero or n.get_real() != floor(n.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (k.get_imag() != LongNumber::zero or k.get_real() != floor(k.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::cinf;
    else if (num == LongComplex::czero)
        return LongComplex::half_Pi;
    return LongComplex::half_Pi - asin(num, n, k);
}

LongComplex many_value_f::atan(const LongComplex &num, const LongComplex &n, const LongComplex &k) {
    if (n.get_imag() != LongNumber::zero or n.get_real() != floor(n.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (k.get_imag() != LongNumber::zero or k.get_real() != floor(k.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::czero;
    auto ln_1 = std::async(std::launch::async, [&num, &n] { return ln(LongComplex::one - LongComplex::I * num, n); }),
            ln_2 = std::async(std::launch::async, [&num, &k] { return ln(LongComplex::one + LongComplex::I * num, k); });
    return LongComplex::half * LongComplex::I * (ln_1.get() - ln_2.get());
}

LongComplex many_value_f::actan(const LongComplex &num, const LongComplex &n, const LongComplex &k) {
    if (n.get_imag() != LongNumber::zero or n.get_real() != floor(n.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (k.get_imag() != LongNumber::zero or k.get_real() != floor(k.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::half_Pi;
    auto ln_1 = std::async(std::launch::async, [&num, &n] { return ln((num - LongComplex::I) / num, n); }),
            ln_2 = std::async(std::launch::async, [&num, &k] { return ln((num + LongComplex::I) / num, k); });
    return LongComplex::half * LongComplex::I * (ln_1.get() - ln_2.get());
}

LongComplex many_value_f::asec(const LongComplex &num, const LongComplex &n, const LongComplex &k) {
    if (n.get_imag() != LongNumber::zero or n.get_real() != floor(n.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (k.get_imag() != LongNumber::zero or k.get_real() != floor(k.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::half_Pi;
    else if (num == LongComplex::czero)
        return LongComplex::cinf;
    return acos(LongComplex::one / num, n, k);
}

LongComplex many_value_f::acosec(const LongComplex &num, const LongComplex &n, const LongComplex &k) {
    if (n.get_imag() != LongNumber::zero or n.get_real() != floor(n.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (k.get_imag() != LongNumber::zero or k.get_real() != floor(k.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::half_Pi;
    else if (num == LongComplex::czero)
        return LongComplex::cinf;
    return asin(LongComplex::one / num, n, k);
}

LongComplex many_value_f::asinh(const LongComplex &num, const LongComplex &n, const LongComplex &k) {
    if (n.get_imag() != LongNumber::zero or n.get_real() != floor(n.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (k.get_imag() != LongNumber::zero or k.get_real() != floor(k.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::cinf;
    else if (num == LongComplex::czero)
        return LongComplex::czero;
    return ln(sqrt(num * num + LongComplex::one, k) + num, n);
}

LongComplex many_value_f::acosh(const LongComplex &num, const LongComplex &n, const LongComplex &k) {
    if (n.get_imag() != LongNumber::zero or n.get_real() != floor(n.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (k.get_imag() != LongNumber::zero or k.get_real() != floor(k.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::cinf;
    else if (num == LongComplex::czero)
        return LongComplex::half_Pi * LongComplex::I;
    auto sqrt_1 = std::async(std::launch::async, [&num] { return sqrt(num + LongComplex::one); }),
            sqrt_2 = std::async(std::launch::async, [&num] { return sqrt(num - LongComplex::one); });
    if (std::stoll(k.get_real().to_string()) % 2 == 0)
        return ln(sqrt_1.get() * sqrt_2.get() + num, n);
    return ln(-sqrt_1.get() * sqrt_2.get() + num, n);
}

LongComplex many_value_f::atanh(const LongComplex &num, const LongComplex &n, const LongComplex &k) {
    if (n.get_imag() != LongNumber::zero or n.get_real() != floor(n.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (k.get_imag() != LongNumber::zero or k.get_real() != floor(k.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::czero;
    auto ln_1 = std::async(std::launch::async, [&num, &n] { return ln(num + LongComplex::one, n); }),
            ln_2 = std::async(std::launch::async, [&num, &k] { return ln(LongComplex::one - num, k); });
    return LongComplex::half * (ln_1.get() - ln_2.get());
}

LongComplex many_value_f::actanh(const LongComplex &num, const LongComplex &n, const LongComplex &k) {
    if (n.get_imag() != LongNumber::zero or n.get_real() != floor(n.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (k.get_imag() != LongNumber::zero or k.get_real() != floor(k.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (iscnan(num))
        return LongComplex::cnan;
    else if (iscinf(num))
        return LongComplex::czero;
    else if (num == LongComplex::czero)
        return LongComplex::half_Pi * LongComplex::I;
    auto ln_1 = std::async(std::launch::async, [&num, &n] { return ln(LongComplex::one / num + LongComplex::one, n); }),
            ln_2 = std::async(std::launch::async, [&num, &k] { return ln(LongComplex::one - LongComplex::one / num, k); });
    return LongComplex::half * (ln_1.get() - ln_2.get());
}

LongComplex many_value_f::asech(const LongComplex &num, const LongComplex &n, const LongComplex &k) {
    if (n.get_imag() != LongNumber::zero or n.get_real() != floor(n.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (k.get_imag() != LongNumber::zero or k.get_real() != floor(k.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::cinf;
    return acosh(LongComplex::one / num, n, k);
}

LongComplex many_value_f::acosech(const LongComplex &num, const LongComplex &n, const LongComplex &k) {
    if (n.get_imag() != LongNumber::zero or n.get_real() != floor(n.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (k.get_imag() != LongNumber::zero or k.get_real() != floor(k.get_real()))
        throw std::logic_error("In multi-digit functions, the argument number must be an integer");
    if (iscnan(num) or iscinf(num))
        return LongComplex::cnan;
    else if (num == LongComplex::czero)
        return LongComplex::cinf;
    return asinh(LongComplex::one / num, n, k);
}
