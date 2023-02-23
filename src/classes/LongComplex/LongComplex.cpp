#include "LongComplex.h"
#include "string"

const LongComplex LongComplex::czero = LongComplex("0");
const LongComplex LongComplex::cinf = LongComplex(LongNumber(cringe("inf")), LongNumber(cringe("inf")));
const LongComplex LongComplex::I = LongComplex("i");

LongComplex::LongComplex(const LongNumber &real_, const LongNumber &imag_) {
    this->real = real_;
    this->imag = imag_;
}

LongComplex::LongComplex(const LongComplex &num) {
    this->real = num.real;
    this->imag = num.imag;
}

LongComplex::LongComplex(std::string s) {
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
}

LongComplex &LongComplex::operator=(const LongComplex &rhs) = default;

LongComplex LongComplex::operator+(const LongComplex &rhs) const {
    return LongComplex(this->real + rhs.real, this->imag + rhs.imag);
}

LongComplex LongComplex::operator-(const LongComplex &rhs) const {
    return LongComplex(this->real - rhs.real, this->imag - rhs.imag);
}

LongComplex LongComplex::operator*(const LongComplex &rhs) const {
    return LongComplex(this->real * rhs.real - this->imag * rhs.imag,
                       this->imag * rhs.real + this->real * rhs.imag);
}

LongComplex LongComplex::operator/(const LongComplex &rhs) const {
    if (*this == LongComplex::czero and *this != LongComplex::czero) {
        return LongComplex::czero;
    } else if (*this != LongComplex::czero and *this == LongComplex::czero) {
        return LongComplex::cinf;
    }
    return LongComplex((this->real * rhs.real + this->imag * rhs.imag) / (rhs.real * rhs.real + rhs.imag * rhs.imag),
                       (this->imag * rhs.real - this->real * rhs.imag) / (rhs.real * rhs.real + rhs.imag * rhs.imag));
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
    LongComplex tmp = *this;
    tmp.real = -this->real;
    tmp.imag = -this->imag;
    return tmp;
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
            if (i == num.size() - 1 or (i <= num.size() - 2 and !(num[i + 1] >= '0' and num[i + 1] <= '9') and num[i + 1] != 'i')) {
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
        std::cout << "cringe\n";
        num = LongComplex::czero;
    }
    return in;
}

std::string LongComplex::to_string() const {
    std::string tmp;
    tmp += this->real.to_string() + (this->imag.sign ? "" : "+") + this->imag.to_string() + "*i";
    return tmp;
}
