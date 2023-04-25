#include "VecND_LN.h"

VecND_LN::VecND_LN(int x_) {
    for (int i = 0; i < x_; ++i) {
        vec.push_back(LongNumber::zero);
    }
}

VecND_LN::VecND_LN() = default;

VecND_LN::VecND_LN(const VecND_LN &el) {
    vec = el.vec;
}

VecND_LN VecND_LN::operator+(const VecND_LN &rhs) const {
    if (this->vec.size() == rhs.vec.size()) {
        VecND_LN tmp((int) rhs.vec.size());
        for (int i = 0; i < rhs.vec.size(); ++i) {
            tmp.vec[i] = this->vec[i] + rhs.vec[i];
        }
        return VecND_LN{tmp};
    }
    throw std::length_error("Incorrect addition: different length of vectors");
}

VecND_LN VecND_LN::operator-(const VecND_LN &rhs) const {
    if (this->vec.size() == rhs.vec.size()) {
        VecND_LN tmp((int) rhs.vec.size());
        for (int i = 0; i < rhs.vec.size(); ++i) {
            tmp.vec[i] = this->vec[i] - rhs.vec[i];
        }
        return VecND_LN{tmp};
    }
    throw std::length_error("Incorrect subtraction: different length of vectors");
}

VecND_LN &VecND_LN::operator=(const VecND_LN &rhs) {
    this->vec.resize(rhs.vec.size());
    for (int i = 0; i < rhs.vec.size(); ++i) {
        copy_with_double_round(this->vec[i], rhs.vec[i]);
    }
    return *this;
}

VecND_LN VecND_LN::operator*(const LongNumber &rhs) const {
    VecND_LN tmp((int) vec.size());
    for (int i = 0; i < vec.size(); ++i) {
        tmp.vec[i] = this->vec[i] * rhs;
    }
    return VecND_LN{tmp};
}

VecND_LN &VecND_LN::operator*=(const LongNumber &rhs) {
    for (int i = 0; i < vec.size(); ++i) {
        this->vec[i] = this->vec[i] * rhs;
    }
    return *this;
}

void VecND_LN::print() {
    std::cout << '(';
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1)
            std::cout << ", ";
    }
    std::cout << ")\n";
}

LongNumber &VecND_LN::operator[](int index) {
    if (index < this->vec.size()) {
        return vec[index];
    }
    throw std::length_error("Vector: Invalid index");
}

const LongNumber &VecND_LN::operator[](int index) const {
    if (index < this->vec.size()) {
        return vec[index];
    }
    throw std::length_error("Vector: Invalid index");
}

int VecND_LN::size() const {
    return (int) vec.size();
}

VecND_LN::VecND_LN(VecND_LN &&el) noexcept {
    vec = std::move(el.vec);
}

VecND_LN &VecND_LN::operator=(VecND_LN &&rhs) noexcept {
    if (this == &rhs)
        return *this;
    vec = std::move(rhs.vec);
    return *this;
}

