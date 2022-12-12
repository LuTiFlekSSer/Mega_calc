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
        num = "0";
    }
    if (num[0] == '-') {
        sign = true;
        num.erase(num.begin());
    } else {
        sign = false;
    }

//    while (num[0] != '.' and num[0] != '0')


    if (num[0] == '.') {
        num.insert(num.begin(), '0');
    }
    if (num[num.size() - 1] == '.') {
        num.insert(num.end(), '0');
    }
    while (num[0] == '0' and num.size() > 1) {
        if (num[1] != '.')
            num.erase(num.begin());
        else
            break;
    }
    if (num.find('.') != std::string::npos) {
        while (num[num.size() - 1] == '0') {
            num.erase(num.end() - 1);
            if (num[num.size() - 1] == '.') {
                num.erase(num.end() - 1);
                break;
            }
        }
    }
    if (num == "0") {
        num.clear();
    }
    long long count = 0;
    bool exp_flag = false, dot_flag = false;
    exp = 0;
    for (char i: num) {
        if (isdigit(i)) {
            ++count;
            if (exp_flag and i != '0') {
                exp = -count + 1;
                exp_flag = false;
            }
            if (!exp_flag)
                numbers.push_back((char) (i - '0'));
        } else if (i == '.') {
            dot_flag = true;
            if (num[0] == '0' and num[1] == '.') {
                exp_flag = true;
                count = 0;
                numbers.clear();
            } else {
                exp = count;
            }
        }
    }
    if (!dot_flag) {
        exp = count;
    }
    if (num.empty()) {
        numbers.push_back(0);
        sign = false;
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

std::strong_ordering LongNumber::operator<=>(const LongNumber &rhs) {
    if (this->sign > rhs.sign) {
        return std::strong_ordering::less;
    } else if (this->sign < rhs.sign) {
        return std::strong_ordering::greater;
    }
    if (this->exp < rhs.exp) {
        return std::strong_ordering::less;
    } else if (this->exp > rhs.exp) {
        return std::strong_ordering::greater;
    }
    if (rhs.exp < 0) {
        if (this->numbers.size() > rhs.numbers.size()) {
            return std::strong_ordering::less;
        } else if (this->numbers.size() < rhs.numbers.size()) {
            return std::strong_ordering::greater;
        } else {
            for (auto i = 0; i < this->numbers.size(); ++i) {
//                if (this->numbers[0])
            }
        }

    }

}

LongNumber &LongNumber::operator=(const LongNumber &rhs) = default;

bool correct_num(const std::string &num) {
    long long dot_num = 0;
    for (int i = 0; i < num.size(); ++i) {
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