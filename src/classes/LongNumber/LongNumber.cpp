#include "LongNumber.h"
#include "iostream"

LongNumber::LongNumber() {
    sign = false;
    numbers.resize(1);
    numbers[0] = 0;
    exp = 0;
}

LongNumber::LongNumber(const LongNumber &num) {
    sign = num.sign;
    numbers = num.numbers;
    exp = num.exp;
}

LongNumber::LongNumber(std::string num) {
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
    while (num[num.size() - 1] == '0') {
        num.erase(num.end() - 1);
        if (num.empty())
            num.insert(num.begin(), '.');
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
        exp = (long long) num.size();
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
}

std::string LongNumber::to_string() const {
    std::string str;
    if (this->sign)
        str.insert(str.begin(), '-');
    if (this->exp < 0) {
        str.append("0.");
        for (int i = 0; i < -exp - 1; ++i) {
            str.insert(str.end(), '0');
        }
        for (char i: this->numbers) {
            str.insert(str.end(), (char) (i + '0'));
        }
    } else {
        for (long long i = 0; i < exp; ++i) {
            str.insert(str.end(), (char) (this->numbers[i] + '0'));
        }
        if (this->exp != 0)
            str.insert(str.end(), '.');
        for (long long i = exp; i < this->numbers.size(); ++i) {
            str.insert(str.end(), (char) (this->numbers[i] + '0'));
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
    if (lhs.sign > rhs.sign) {
        return std::strong_ordering::less;
    } else if (lhs.sign < rhs.sign) {
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

LongNumber &LongNumber::operator=(const LongNumber &rhs) = default;

bool correct_num(const std::string &num) {
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