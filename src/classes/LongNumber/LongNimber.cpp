#include "LongNimber.h"
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
    if (num[0] == '-') {
        sign = true;
        num.erase(num.begin());
    } else {
        sign = false;
    }
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
    bool exp_flag = false;
    exp = 0;
    for (char i: num) {
        if (isdigit(i)) {
            ++count;
            if (exp_flag and i != '0') {
                exp = -count;
                exp_flag = false;
            }
            if (!exp_flag)
                numbers.push_back((char) (i - '0'));
        } else if (i == '.') {
            if (num[0] == '0' and num[1] == '.') {
                exp_flag = true;
                count = 0;
                numbers.clear();
            } else {
                exp = count;
            }
        }
    }
    if (num.empty()) {
        numbers.push_back(0);
        sign = false;
    }
}

std::string LongNumber::to_string() {
    std::string str;
    if (this->sign)
        str.insert(str.begin(), '-');
    if (this->exp < 0) {
        str.append("0.");
        for (int i = 0; i < -exp; ++i) {
            str.insert(str.end(), '0');
        }
        for (char i: this->numbers) {
            str.insert(str.end(), (char) (i + '0'));
        }
    } else {
        for (int i = 0; i < exp; ++i) {
            str.insert(str.end(), (char) (this->numbers[i] + '0'));
        }
        if (this->exp != 0)
            str.insert(str.end(), '.');
        for (int i = exp; i < this->numbers.size(); ++i) {
            str.insert(str.end(), (char) (this->numbers[i] + '0'));
        }
    }
    return str;
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