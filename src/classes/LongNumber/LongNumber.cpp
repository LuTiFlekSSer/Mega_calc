#include "LongNumber.h"
#include "iostream"

const LongNumber LongNumber::zero = LongNumber{0};
const LongNumber LongNumber::Pi = LongNumber("3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679");
const LongNumber LongNumber::e = LongNumber("2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274");
const LongNumber LongNumber::nan = LongNumber(cringe("nan"));
const LongNumber LongNumber::inf = LongNumber(cringe("inf"));
const LongNumber LongNumber::infm = LongNumber(cringe("-inf"));

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
        if (this->numbers.size() > this->exp) {
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
        throw std::logic_error("One number is NaN");
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
                for (long long i = (long long) this->numbers.size() - 1; i > null_to_pad_left; --i) {
                    char curr_diff = (char) (this->numbers[i] - rhs.numbers[i - null_to_pad_left] - (char) minus_1);
                    if (curr_diff < 0) {
                        minus_1 = true;
                        answer[i] = (char) (10 + curr_diff);
                    } else {
                        minus_1 = false;
                        answer[i] = curr_diff;
                    }
                }
                for (long long i = null_to_pad_left - 1; i > (long long) this->numbers.size() - 1; --i) {
                    char curr_diff = (char) -minus_1;
                    if (curr_diff < 0) {
                        minus_1 = true;
                        answer[i] = (char) (10 + curr_diff);
                    } else {
                        minus_1 = false;
                        answer[i] = curr_diff;
                    }
                }
                for (long long i = (long long) this->numbers.size() - 1; i >= 0; --i) {
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


LongNumber &LongNumber::operator=(const LongNumber &rhs) = default;

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
