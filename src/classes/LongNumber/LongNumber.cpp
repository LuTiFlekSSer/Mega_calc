#include "LongNumber.h"
#include "iostream"

const LongNumber LongNumber::zero = LongNumber{0};
const LongNumber LongNumber::one = LongNumber{1};
const LongNumber LongNumber::two = LongNumber{2};
const LongNumber LongNumber::Pi = LongNumber("3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679");
const LongNumber LongNumber::e = LongNumber("2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274");
const LongNumber LongNumber::nan = LongNumber(cringe("nan"));
const LongNumber LongNumber::inf = LongNumber(cringe("inf"));
const LongNumber LongNumber::infm = LongNumber(cringe("-inf"));
const LongNumber LongNumber::eps = LongNumber("0.00000000000000001");

static const LongNumber G("6.024680040776729583740234375");
static const LongNumber lanczos_num_coeffs[13] = {
        LongNumber("23531376880.410759688572007674451636754734846804940"),
        LongNumber("42919803642.649098768957899047001988850926355848959"),
        LongNumber("35711959237.355668049440185451547166705960488635843"),
        LongNumber("17921034426.037209699919755754458931112671403265390"),
        LongNumber("6039542586.3520280050642916443072979210699388420708"),
        LongNumber("1439720407.3117216736632230727949123939715485786772"),
        LongNumber("248874557.86205415651146038641322942321632125127801"),
        LongNumber("31426415.585400194380614231628318205362874684987640"),
        LongNumber("2876370.6289353724412254090516208496135991145378768"),
        LongNumber("186056.26539522349504029498971604569928220784236328"),
        LongNumber("8071.6720023658162106380029022722506138218516325024"),
        LongNumber("210.82427775157934587250973392071336271166969580291"),
        LongNumber("2.5066282746310002701649081771338373386264310793408")
};
static const LongNumber lanczos_den_coeffs[13] = {
        LongNumber("0"),
        LongNumber("39916800"),
        LongNumber("120543840"),
        LongNumber("150917976"),
        LongNumber("105258076"),
        LongNumber("45995730"),
        LongNumber("13339535"),
        LongNumber("2637558"),
        LongNumber("357423"),
        LongNumber("32670"),
        LongNumber("1925"),
        LongNumber("66"),
        LongNumber("1")
};

LongNumber LongNumber::operator/(const LongNumber &rhs) const {
    if (isnan(*this) or isnan(rhs) or (*this == LongNumber::zero and rhs == LongNumber::zero) or ((isinf(*this) or isinfm(*this)) and (isinf(rhs) or isinfm(rhs))))
        return LongNumber::nan;
    else if (isinf(rhs) or isinfm(rhs))
        return LongNumber::zero;
    else if (rhs == LongNumber::zero)
        return LongNumber::inf;
    return *this * rhs.inv();
}

LongNumber::LongNumber() {
    sign = false;
    numbers.resize(1);
    numbers[0] = 0;
    exp = 1;
}

LongNumber::LongNumber(const LongNumber &num) {
    sign = num.sign;
    numbers = num.numbers;
    exp = num.exp;
//    this->round();
}

LongNumber::LongNumber(std::string num) { //∞ из потока
    if (num == "inf") {
        *this = LongNumber::inf;
        return;
    } else if (num == "-inf") {
        *this = LongNumber::infm;
        return;
    }
    exp = 0;
    if (num.empty()) {
        num = ".";
    }
    if (num[0] == '-') {
        sign = true;
        num.erase(num.begin());
        if (num.empty())
            num.insert(num.begin(), '.');
    } else {
        sign = false;
    }
    while (num[0] == '0') {
        num.erase(num.begin());
        if (num.empty())
            num.insert(num.begin(), '.');
    }
    long long add_exp = 0;
    if (num.find('.') != std::string::npos)
        while (num[num.size() - 1] == '0') {
            num.erase(num.end() - 1);
            if (num.empty())
                num.insert(num.begin(), '.');
        }
    else
        while (num[num.size() - 1] == '0') {
            ++add_exp;
            num.erase(num.end() - 1);
        }
    if (num == ".") {
        if (sign)
            sign = false;
        num = ".0";
    }
    if (num[0] == '.') {
        for (long long i = 1; i < num.size(); ++i)
            if (num[i] != '0') {
                exp = 1 - i;
                break;
            }
        for (long long i = -exp + 1; i < num.size(); ++i)
            numbers.push_back((char) (num[i] - '0'));
    } else {
        exp = (long long) num.size() + add_exp;
        for (long long i = 0; i < num.size(); ++i) {
            if (num[i] == '.') {
                exp = i;
                break;
            }
            numbers.push_back((char) (num[i] - '0'));
        }
        for (long long i = exp + 1; i < num.size(); ++i)
            numbers.push_back((char) (num[i] - '0'));
    }
    if (numbers.size() == 1 and numbers[0] == 0)
        exp = 1;
}

std::string LongNumber::to_string() const {
    if (*this == LongNumber::nan) {
        return "NaN";
    } else if (*this == LongNumber::inf) {
        return "inf";
    } else if (*this == LongNumber::infm) {
        return "-inf";
    }
    std::string str;
    if (this->sign)
        str.push_back('-');
    if (this->exp <= 0) {
        str.append("0.");
        for (int i = 0; i < -exp; ++i) {
            str.push_back('0');
        }
        for (char i: this->numbers) {
            str.push_back((char) (i + '0'));
        }
    } else {
        for (long long i = 0; i < std::min(exp, (long long) numbers.size()); ++i) {
            str.push_back((char) (this->numbers[i] + '0'));
        }
        if ((long long) this->numbers.size() > this->exp) {
            str.push_back('.');
            for (long long i = exp; i < this->numbers.size(); ++i) {
                str.push_back((char) (this->numbers[i] + '0'));
            }
        } else {
            for (auto i = (long long) numbers.size(); i < exp; ++i) {
                str.push_back('0');
            }
        }
    }
    return str;
}

std::ostream &operator<<(std::ostream &out, const LongNumber &num) {
    out << num.to_string();
    return out;
}


std::istream &operator>>(std::istream &in, LongNumber &num) {
    std::string s_num;
    in >> s_num;
    if (correct_num(s_num))
        num = LongNumber(s_num);
    else
        num = LongNumber(0);
    return in;
}

std::strong_ordering operator<=>(const LongNumber &lhs, const LongNumber &rhs) {
    if (isnan(lhs) or isnan(rhs)) {
        throw std::logic_error("Incorrect comparison: one number is NaN");
    }
    if (lhs == rhs) {
        return std::strong_ordering::equivalent;
    }
    if (lhs.sign > rhs.sign) {
        return std::strong_ordering::less;
    } else if (lhs.sign < rhs.sign) {
        return std::strong_ordering::greater;
    }
    if (isinfm(lhs) or isinf(rhs) or (lhs == LongNumber::zero and !rhs.sign) or (lhs.sign and rhs == LongNumber::zero)) {
        return std::strong_ordering::less;
    } else if (isinf(lhs) or isinfm(rhs) or (lhs == LongNumber::zero and rhs.sign) or (!lhs.sign and rhs == LongNumber::zero)) {
        return std::strong_ordering::greater;
    }
    if (lhs.exp < rhs.exp) {
        return std::strong_ordering::less;
    } else if (lhs.exp > rhs.exp) {
        return std::strong_ordering::greater;
    }
    for (long long i = 0; i < std::min(lhs.numbers.size(), rhs.numbers.size()); ++i) {
        if (lhs.numbers[i] > rhs.numbers[i]) {
            return lhs.sign ? std::strong_ordering::less : std::strong_ordering::greater;
        } else if (lhs.numbers[i] < rhs.numbers[i]) {
            return lhs.sign ? std::strong_ordering::greater : std::strong_ordering::less;
        }
    }
    if (lhs.numbers.size() > rhs.numbers.size()) {
        return lhs.sign ? std::strong_ordering::less : std::strong_ordering::greater;
    } else if (lhs.numbers.size() < rhs.numbers.size()) {
        return lhs.sign ? std::strong_ordering::greater : std::strong_ordering::less;
    }
    return std::strong_ordering::equivalent;
}

bool operator!=(const LongNumber &lhs, const LongNumber &rhs) {
    if (lhs.sign != rhs.sign or lhs.exp != rhs.exp or lhs.numbers != rhs.numbers)
        return true;
    return false;
}

bool operator==(const LongNumber &lhs, const LongNumber &rhs) {
    if (lhs.sign != rhs.sign or lhs.exp != rhs.exp or lhs.numbers != rhs.numbers)
        return false;
    return true;
}

LongNumber LongNumber::operator+(const LongNumber &rhs) const {
    if (isnan(*this) or isnan(rhs)) {
        return LongNumber::nan;
    }
    if (this->sign == rhs.sign) {
        if (isinf(*this) or isinfm(*this))
            return *this;
        else if (isinf(rhs) or isinfm(rhs))
            return rhs;
        bool num_with_right_pad = (long long) this->numbers.size() - this->exp >= (long long) rhs.numbers.size() - rhs.exp,
                num_with_left_pad = this->exp > rhs.exp;
        if (!num_with_right_pad)
            return rhs + *this;
        long long null_to_pad_left = std::abs(this->exp - rhs.exp);
        long long null_to_pad_right = std::abs((long long) this->numbers.size() - this->exp - ((long long) rhs.numbers.size() - rhs.exp));
        long long ans_size;
        if (num_with_left_pad == num_with_right_pad) {
            ans_size = (long long) std::max(this->numbers.size(), rhs.numbers.size());
        } else if (!num_with_left_pad) {
            ans_size = null_to_pad_left + (long long) this->numbers.size();
        } else {
            ans_size = null_to_pad_right + (long long) this->numbers.size();
        }
        long long max_exp = std::max(this->exp, rhs.exp);
        std::vector<char> answer(ans_size);
        bool plus_1 = false;
        if (num_with_left_pad) {
            for (long long i = (long long) this->numbers.size() - 1; i >= null_to_pad_left + rhs.numbers.size(); --i) {
                answer[i] = this->numbers[i];
            }
            for (long long i = null_to_pad_left + (long long) rhs.numbers.size() - 1; i >= null_to_pad_left; --i) {
                char curr_sum = (char) (rhs.numbers[i - null_to_pad_left] + this->numbers[i] + (char) plus_1);
                if (curr_sum > 9) {
                    plus_1 = true;
                    answer[i] = (char) (curr_sum - 10);
                } else {
                    plus_1 = false;
                    answer[i] = curr_sum;
                }
            }
            for (long long i = null_to_pad_left - 1; i >= 0; --i) {
                char curr_sum = (char) (this->numbers[i] + (char) plus_1);
                if (curr_sum > 9) {
                    plus_1 = true;
                    answer[i] = (char) (curr_sum - 10);
                } else {
                    plus_1 = false;
                    answer[i] = curr_sum;
                }
            }
        } else {
            for (long long i = (long long) this->numbers.size() + null_to_pad_left - 1; i >= std::max((long long) rhs.numbers.size(), null_to_pad_left); --i) {
                answer[i] = this->numbers[i - null_to_pad_left];
            }
            for (long long i = (long long) rhs.numbers.size() - 1; i >= null_to_pad_left; --i) {
                char curr_sum = (char) (rhs.numbers[i] + this->numbers[i - null_to_pad_left] + (char) plus_1);
                if (curr_sum > 9) {
                    plus_1 = true;
                    answer[i] = (char) (curr_sum - 10);
                } else {
                    plus_1 = false;
                    answer[i] = curr_sum;
                }
            }
            for (long long i = std::min((long long) rhs.numbers.size(), null_to_pad_left) - 1; i >= 0; --i) {
                char curr_sum = (char) (rhs.numbers[i] + (char) plus_1);
                if (curr_sum > 9) {
                    plus_1 = true;
                    answer[i] = (char) (curr_sum - 10);
                } else {
                    plus_1 = false;
                    answer[i] = curr_sum;
                }
            }
        }
        if (plus_1) {
            ++max_exp;
            answer.insert(answer.begin(), 1);
        }
        while (answer[answer.size() - 1] == 0) {
            answer.erase(answer.end() - 1);
            if (answer.empty())
                return LongNumber{};
        }
        while (answer[0] == 0) {
            answer.erase(answer.begin());
            --max_exp;
            if (answer.empty())
                return LongNumber{};
        }
        LongNumber tmp{};
        tmp.numbers = answer;
        tmp.sign = this->sign;
        tmp.exp = max_exp;
        return tmp;
    }
    return *this - -rhs;
}


LongNumber LongNumber::operator-(const LongNumber &rhs) const {
    if (isnan(*this) or isnan(rhs) or (isinf(*this) and isinf(rhs)) or (isinfm(*this) and isinfm(rhs))) {
        return LongNumber::nan;
    }
    if (rhs == LongNumber::zero)
        return *this;
    if (this->sign == rhs.sign) {
        if (isinf(*this) or isinfm(*this))
            return *this;
        else if (isinf(rhs) or isinfm(rhs))
            return -rhs;
        if (this->sign)
            return -(abs(*this) - abs(rhs));
        if (*this < rhs)
            return -(rhs - *this);
        bool num_with_right_pad = (long long) this->numbers.size() - this->exp >= (long long) rhs.numbers.size() - rhs.exp,
                num_with_left_pad = this->exp > rhs.exp;
        long long null_to_pad_left = std::abs(this->exp - rhs.exp);
        long long null_to_pad_right = std::abs((long long) this->numbers.size() - this->exp - ((long long) rhs.numbers.size() - rhs.exp));
        long long ans_size;
        if (num_with_left_pad == num_with_right_pad) {
            ans_size = (long long) std::max(this->numbers.size(), rhs.numbers.size());
        } else if (!num_with_left_pad) {
            ans_size = null_to_pad_left + (long long) this->numbers.size();
        } else {
            ans_size = null_to_pad_right + (long long) this->numbers.size();
        }
        long long max_exp = std::max(this->exp, rhs.exp);
        std::vector<char> answer(ans_size);
        bool minus_1 = false;
        if (num_with_right_pad) {
            if (num_with_left_pad) {
                for (long long i = (long long) this->numbers.size() - 1; i >= null_to_pad_left + rhs.numbers.size(); --i) {
                    answer[i] = this->numbers[i];
                }
                for (long long i = null_to_pad_left + (long long) rhs.numbers.size() - 1; i >= null_to_pad_left; --i) {
                    char curr_diff = (char) (this->numbers[i] - rhs.numbers[i - null_to_pad_left] - (char) minus_1);
                    if (curr_diff < 0) {
                        minus_1 = true;
                        answer[i] = (char) (10 + curr_diff);
                    } else {
                        minus_1 = false;
                        answer[i] = curr_diff;
                    }
                }
                for (long long i = null_to_pad_left - 1; i >= 0; --i) {
                    char curr_diff = (char) (this->numbers[i] - (char) minus_1);
                    if (curr_diff < 0) {
                        minus_1 = true;
                        answer[i] = (char) (10 + curr_diff);
                    } else {
                        minus_1 = false;
                        answer[i] = curr_diff;
                    }
                }
            } else {
                for (long long i = (long long) this->numbers.size() + null_to_pad_left - 1; i >= std::max((long long) rhs.numbers.size(), null_to_pad_left); --i) {
                    answer[i] = this->numbers[i - null_to_pad_left];
                }
                for (long long i = (long long) rhs.numbers.size() - 1; i >= null_to_pad_left; --i) {
                    char curr_diff = (char) (this->numbers[i - null_to_pad_left] - rhs.numbers[i] - (char) minus_1);
                    if (curr_diff < 0) {
                        minus_1 = true;
                        answer[i] = (char) (10 + curr_diff);
                    } else {
                        minus_1 = false;
                        answer[i] = curr_diff;
                    }
                }
            }
        } else {
            if (!num_with_left_pad) {
                for (long long i = (long long) rhs.numbers.size() - 1; i >= (long long) this->numbers.size() + null_to_pad_left; --i) {
                    char curr_diff = (char) -(rhs.numbers[i] + (char) minus_1);
                    if (curr_diff < 0) {
                        minus_1 = true;
                        answer[i] = (char) (10 + curr_diff);
                    } else {
                        minus_1 = false;
                        answer[i] = curr_diff;
                    }
                }
                for (long long i = null_to_pad_left + (long long) this->numbers.size() - 1; i >= null_to_pad_left; --i) {
                    char curr_diff = (char) (this->numbers[i - null_to_pad_left] - rhs.numbers[i] - (char) minus_1);
                    if (curr_diff < 0) {
                        minus_1 = true;
                        answer[i] = (char) (10 + curr_diff);
                    } else {
                        minus_1 = false;
                        answer[i] = curr_diff;
                    }
                }
            } else {
                for (long long i = (long long) this->numbers.size() + null_to_pad_right - 1; i >= std::max((long long) this->numbers.size(), null_to_pad_left); --i) {
                    char curr_diff = (char) -(rhs.numbers[i - null_to_pad_left] + (char) minus_1);
                    if (curr_diff < 0) {
                        minus_1 = true;
                        answer[i] = (char) (10 + curr_diff);
                    } else {
                        minus_1 = false;
                        answer[i] = curr_diff;
                    }
                }
                for (long long i = (long long) this->numbers.size() - 1; i >= null_to_pad_left; --i) {
                    char curr_diff = (char) (this->numbers[i] - rhs.numbers[i - null_to_pad_left] - (char) minus_1);
                    if (curr_diff < 0) {
                        minus_1 = true;
                        answer[i] = (char) (10 + curr_diff);
                    } else {
                        minus_1 = false;
                        answer[i] = curr_diff;
                    }
                }
                for (long long i = null_to_pad_left - 1; i >= (long long) this->numbers.size(); --i) {
                    char curr_diff = (char) -minus_1;
                    if (curr_diff < 0) {
                        minus_1 = true;
                        answer[i] = (char) (10 + curr_diff);
                    } else {
                        minus_1 = false;
                        answer[i] = curr_diff;
                    }
                }
                for (long long i = std::min((long long) this->numbers.size(), null_to_pad_left) - 1; i >= 0; --i) {
                    char curr_diff = (char) (this->numbers[i] - (char) minus_1);
                    if (curr_diff < 0) {
                        minus_1 = true;
                        answer[i] = (char) (10 + curr_diff);
                    } else {
                        minus_1 = false;
                        answer[i] = curr_diff;
                    }
                }
            }
        }
        while (answer[0] == 0) {
            --max_exp;
            answer.erase(answer.begin());
            if (answer.empty())
                return LongNumber{};
        }
        while (answer[answer.size() - 1] == 0) {
            answer.erase(answer.end() - 1);
            if (answer.empty())
                return LongNumber{};
        }
        LongNumber tmp{};
        tmp.numbers = answer;
        tmp.sign = this->sign;
        tmp.exp = max_exp;
        return tmp;
    }
    return *this + -rhs;
}

LongNumber LongNumber::operator-() const {
    if (*this == LongNumber::zero or isnan(*this))
        return *this;
    LongNumber tmp = *this;
    tmp.sign = !tmp.sign;
    return tmp;
}

LongNumber::LongNumber(const cringe &par) {
    if (par.par == "inf") {
        sign = false;
        numbers.resize(1);
        numbers[0] = 11;
        exp = 0;
    } else if (par.par == "nan") {
        sign = false;
        numbers.resize(1);
        numbers[0] = 10;
        exp = 0;
    } else if (par.par == "-inf") {
        sign = true;
        numbers.resize(1);
        numbers[0] = 11;
        exp = 0;
    }
}


LongNumber LongNumber::operator*(const LongNumber &rhs) const {
    if (isnan(*this) or isnan(rhs) or (*this == LongNumber::zero and (isinf(rhs) or isinfm(rhs))) or (rhs == LongNumber::zero and (isinf(*this) or isinfm(*this)))) {
        return LongNumber::nan;
    } else if (*this == LongNumber::zero or rhs == LongNumber::zero) {
        return LongNumber::zero;
    } else if (isinf(abs(*this)) or isinf(abs(rhs))) {
        return rhs.sign ^ this->sign ? LongNumber::infm : LongNumber::inf;
    }
    unsigned long long len = rhs.numbers.size() + this->numbers.size();
    std::vector<unsigned long long> answer(len);
    LongNumber tmp{};
    for (unsigned long long i = 0; i < rhs.numbers.size(); ++i) {
        for (unsigned long long j = 0; j < this->numbers.size(); ++j) {
            answer[i + j + 1] += rhs.numbers[i] * this->numbers[j];
        }
    }
    tmp.numbers.resize(len);
    tmp.sign = this->sign ^ rhs.sign;
    tmp.exp = this->exp + rhs.exp;
    for (auto i = len - 1; i > 0; i--) {
        answer[i - 1] += answer[i] / 10;
        tmp.numbers[i] = (char) (answer[i] % 10);
    }
    tmp.numbers[0] = (char) answer[0];
    while (tmp.numbers[0] == 0) {
        --tmp.exp;
        tmp.numbers.erase(tmp.numbers.begin());
    }
    while (tmp.numbers[tmp.numbers.size() - 1] == 0) {
        tmp.numbers.erase(tmp.numbers.end() - 1);
    }
    return tmp;
}

LongNumber pow(const LongNumber &num, const LongNumber &deg) {//nan для дробной степени и отрицательного числа
    if (isnan(num) or isnan(deg) or (num == LongNumber::zero and deg == LongNumber::zero) or (num == LongNumber::one and (isinf(deg) or isinfm(deg))) or
        ((isinf(num) or isinfm(num)) and deg == LongNumber::zero))
        return LongNumber::nan;
    else if (deg == LongNumber::zero)
        return LongNumber::one;
    else if ((abs(num) < LongNumber::one and isinf(deg)) or (abs(num) > LongNumber::one and isinfm(deg)) or num == LongNumber::zero)
        return LongNumber::zero;
    else if ((abs(num) < LongNumber::one and isinfm(deg)) or (abs(num) > LongNumber::one and isinf(deg)))
        return LongNumber::inf;
    else if ((long long) deg.numbers.size() - deg.exp <= 0) {
        LongNumber tmp1 = deg.sign ? num.inv() : num, tmp2 = tmp1;
        for (auto i = LongNumber::one; i < abs(deg); ++i) {
            tmp2 *= tmp1;
        }
        return tmp2;
    }
    return exp(ln(num) * deg);
}

void LongNumber::round() {
    if (isinf(*this) or isinfm(*this) or isnan(*this))
        return;
    long long flag = (long long) this->numbers.size() - this->exp;
    if (flag >= -LongNumber::eps.exp + 2ll) {
        bool old_sign = this->sign;
        if (this->exp - LongNumber::eps.exp + 1ll < 0) {
            *this = LongNumber::zero;
            return;
        }
        char tmp = this->numbers[this->exp - LongNumber::eps.exp + 1ll];
        this->numbers.erase(this->numbers.begin() + this->exp - LongNumber::eps.exp + 1ll, this->numbers.end());
        while ((long long) this->numbers.size() > 0 and (long long) this->numbers.size() >= this->exp and this->numbers[this->numbers.size() - 1] == 0) {
            this->numbers.erase(this->numbers.end() - 1);
        }
        while ((long long) this->numbers.size() > 0 and this->numbers[this->numbers.size() - 1] == 0) {
            ++this->exp;
            this->numbers.erase(this->numbers.end() - 1);
        }
        if (this->numbers.empty()) {
            *this = LongNumber::zero;
        }
        if (tmp >= 5) {
            *this += old_sign ? -LongNumber::eps : LongNumber::eps;
        }
    }
}

LongNumber sin(const LongNumber &num) {
    if (isnan(num) or isinf(abs(num)))
        return LongNumber::nan;
    else if (num == LongNumber::zero)
        return num;
    LongNumber tmp = LongNumber::zero, buf = num, count = LongNumber::two;
    bool flag = true;
    while (abs(buf) > LongNumber::eps) {
        tmp += flag ? buf : -buf;
        buf *= num * num / (count * (count + LongNumber::one));
        count += LongNumber::two;
        flag = !flag;
    }
    return tmp;
}

LongNumber exp(const LongNumber &num) {
    if (isnan(num))
        return LongNumber::nan;
    else if (isinf(num))
        return LongNumber::inf;
    else if (isinfm(num))
        return LongNumber::zero;
    else if (num == LongNumber::zero)
        return LongNumber::one;
    LongNumber tmp = LongNumber::one, buf = LongNumber::one, count = LongNumber::one;
    while (abs(buf) > LongNumber::eps) {
        buf *= num / count;
        tmp += buf;
        ++count;
    }
    return tmp;
}

LongNumber ln(const LongNumber &num) {
    if (isnan(num) or num.sign)
        return LongNumber::nan;
    else if (isinf(num))
        return LongNumber::inf;
    else if (num == LongNumber::zero)
        return LongNumber::infm;
    LongNumber a = num < LongNumber::one ? num.inv() : num, x0 = LongNumber(a.exp - 1) * LongNumber(2.30259), buf = LongNumber::one;
    if (isinf(a))
        return LongNumber::infm;
    while (abs(buf) > LongNumber::eps) {
        buf = a / exp(x0) - LongNumber::one;
        x0 += buf;
    }
    return num < LongNumber::one ? -x0 : x0;
}

LongNumber log(const LongNumber &num, const LongNumber &base) {
    if (isnan(base) or isnan(num) or (base == LongNumber::zero and num == LongNumber::zero) or (base == LongNumber::one and num == LongNumber::one) or num.sign or base.sign or
        (isinf(base) and isinf(num)))
        return LongNumber::nan;
    else if (base == LongNumber::zero or num == LongNumber::one or isinf(base))
        return LongNumber::zero;
    else if (base == LongNumber::one or (num == LongNumber::zero and base < LongNumber::one) or (base > LongNumber::one and isinf(num)))
        return LongNumber::inf;
    else if ((num == LongNumber::zero and base > LongNumber::one) or (base < LongNumber::one and isinf(num)))
        return LongNumber::infm;
    return ln(num) / ln(base);
}

LongNumber rec_fact(const LongNumber &num) {
    if (num == LongNumber::zero)
        return LongNumber::one;
    return num * rec_fact(num - LongNumber::one);
}

LongNumber factorial(const LongNumber &num) {
    if (isnan(num))
        return LongNumber::nan;
    else if (isinf(num) or isinfm(num))
        return LongNumber::inf;
    else if ((long long) num.numbers.size() - num.exp <= 0) {
        if (num.sign)
            return LongNumber::inf;
        return rec_fact(num);
    }
    long long num_exp = num.exp;
    LongNumber num_num = num - floor(num) + LongNumber::one, G_minus = G - LongNumber(0.5), y = num_num + G_minus, la1, la2;
    for (int i = 12; i >= 0; --i) {
        la2 = la2 * num_num + lanczos_num_coeffs[i];
        la1 = la1 * num_num + lanczos_den_coeffs[i];
    }
    LongNumber la_rez = la2 / la1, r = la_rez / exp(y);
    r *= pow(y, num_num - LongNumber(0.5));
    for (auto i = num; i >= LongNumber::one; --i) {
        r *= i;
    }
    for (auto i = num + LongNumber::one; i <= LongNumber::one; ++i) {
        r /= i;
    }
    return r;
}

LongNumber floor(const LongNumber &num) {
    if (isnan(num) or isinf(abs(num)))
        return num;
    else if (num.exp <= 0 or num == LongNumber::zero)
        return num.sign ? -LongNumber::one : LongNumber::zero;
    LongNumber tmp;
    tmp.numbers.resize(std::min(num.exp, (long long) num.numbers.size()));
    for (long long i = 0; i < num.exp; ++i) {
        if (i < num.numbers.size())
            tmp.numbers[i] = num.numbers[i];
        else
            break;
    }
    tmp.exp = num.exp;
    if (num.sign and (long long) num.numbers.size() - num.exp > 0)
        tmp += LongNumber::one;
    tmp.sign = num.sign;
    return tmp;
}

LongNumber ceil(const LongNumber &num) {
    return num == floor(num) ? num : floor(num) + LongNumber::one;
}

LongNumber sqrt(const LongNumber &num) {
    if (isnan(num) or isinfm(num) or num < LongNumber::zero)
        return LongNumber::nan;
    else if (isinf(num))
        return LongNumber::inf;
    else if (num == LongNumber::zero)
        return num;
    LongNumber x = LongNumber::inf, half(0.5), x1 = LongNumber::one, new_eps = pow(LongNumber(10), num.exp / 2) * LongNumber::eps;
    while (abs(x1 - x) > new_eps) {
        x = x1;
        x1 = half * (x + num / x);
    }
    return x;
}

LongNumber surd(const LongNumber &num, const LongNumber &deg) {
    if (isnan(num) or (num < LongNumber::zero and (!isinf(abs(deg)) and (floor(deg) != deg or floor(deg) == deg and (deg.numbers.size() != deg.exp or deg.numbers[0] % 2 == 0)))) or
        deg == LongNumber::zero or (isinf(abs(deg)) and num == LongNumber::zero))
        return LongNumber::nan;
    else if (isinf(abs(deg)))
        return LongNumber::one;
    LongNumber tmp = exp(deg.inv() * ln(abs(num)));
    tmp.sign = num.sign;
    return tmp;
}

LongNumber LongNumber::inv() const {
    if (isnan(*this))
        return LongNumber::nan;
    else if (isinf(*this) or isinfm(*this))
        return LongNumber::zero;
    else if (*this == LongNumber::zero)
        return LongNumber::inf;
    LongNumber alpha("2.823529411"), beta("1.8823529411"), x0, tmp(abs(*this)), delta;
    delta = LongNumber(5 / tmp.numbers[0]);
    if (tmp.numbers[0] < 5)
        tmp = tmp * delta;
    else
        delta = LongNumber::one;
    long long tmp_exp = -tmp.exp;
    tmp.exp = 0;
    if (tmp.numbers[0] == 0)
        return this->sign ? LongNumber::infm : LongNumber::inf;
    x0 = alpha - beta * tmp;
    LongNumber gamma(abs(LongNumber::one - tmp * x0));
    while (gamma > LongNumber::eps) {
        gamma *= gamma;
        x0 *= LongNumber::two - tmp * x0;
    }
    x0 *= delta;
    x0.exp += tmp_exp;
    x0.sign = this->sign;
    return x0;
}

LongNumber &LongNumber::operator+=(const LongNumber &rhs) {
    *this = *this + rhs;
    return *this;
}

LongNumber &LongNumber::operator-=(const LongNumber &rhs) {
    *this = *this - rhs;
    return *this;
}

LongNumber &LongNumber::operator/=(const LongNumber &rhs) {
    *this = *this / rhs;
    return *this;
}

LongNumber &LongNumber::operator*=(const LongNumber &rhs) {
    *this = *this * rhs;
    return *this;
}

LongNumber &LongNumber::operator++() {
    *this += LongNumber::one;
    return *this;
}

LongNumber LongNumber::operator++(int) {
    LongNumber old = *this;
    operator++();
    return old;
}

LongNumber LongNumber::operator--(int) {
    LongNumber old = *this;
    operator--();
    return old;
}

LongNumber &LongNumber::operator--() {
    *this -= LongNumber::one;
    return *this;
}

LongNumber abs(const LongNumber &num) {
    return num >= LongNumber::zero ? num : -num;
}

LongNumber max(const LongNumber &num1, const LongNumber &num2) {
    return num1 >= num2 ? num1 : num2;
}

LongNumber min(const LongNumber &num1, const LongNumber &num2) {
    return num1 <= num2 ? num1 : num2;
}

bool isnan(const LongNumber &num) {
    return num == LongNumber::nan;
}

bool isinf(const LongNumber &num) {
    return num == LongNumber::inf;
}

bool isinfm(const LongNumber &num) {
    return num == LongNumber::infm;
}


LongNumber &LongNumber::operator=(const LongNumber &rhs) {
    exp = rhs.exp;
    numbers = rhs.numbers;
    sign = rhs.sign;
    this->round();
    return *this;
}

bool correct_num(const std::string &num) {
    if (num == "inf" or num == "-inf") {
        return true;
    }
    long long dot_num = 0;
    for (long long i = 0; i < num.size(); ++i) {
        if (!isdigit(num[i])) {
            if (num[i] == '-' and i == 0) {
                continue;
            } else if (num[i] == '.' and dot_num == 0) {
                ++dot_num;
            } else {
                return false;
            }
        }
    }
    return true;
}

LongNumber::~LongNumber() = default;
