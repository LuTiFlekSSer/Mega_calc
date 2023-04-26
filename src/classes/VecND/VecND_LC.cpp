#include "VecND_LC.h"

VecND_LC::VecND_LC(int x_) {
    for (int i = 0; i < x_; ++i) {
        vec.push_back(LongComplex::czero);
    }
}

VecND_LC::VecND_LC() = default;

VecND_LC::VecND_LC(const VecND_LC &el) {
    this->vec.resize(el.vec.size());
    for (int i = 0; i < el.vec.size(); ++i) {
        copy_with_double_round(this->vec[i], el.vec[i]);
    }
}

VecND_LC VecND_LC::operator+(const VecND_LC &rhs) const {
    if (this->vec.size() == rhs.vec.size()) {
        VecND_LC tmp((int) rhs.vec.size());
        for (int i = 0; i < rhs.vec.size(); ++i) {
            move_with_double_round(tmp.vec[i], this->vec[i] + rhs.vec[i]);
        }
        return VecND_LC{tmp};
    }
    throw std::length_error("Incorrect addition: different length of vectors");
}

VecND_LC VecND_LC::operator-(const VecND_LC &rhs) const {
    if (this->vec.size() == rhs.vec.size()) {
        VecND_LC tmp((int) rhs.vec.size());
        for (int i = 0; i < rhs.vec.size(); ++i) {
            move_with_double_round(tmp.vec[i], this->vec[i] - rhs.vec[i]);
        }
        return VecND_LC{tmp};
    }
    throw std::length_error("Incorrect subtraction: different length of vectors");
}

VecND_LC &VecND_LC::operator=(const VecND_LC &rhs) {
    this->vec.resize(rhs.vec.size());
    for (int i = 0; i < rhs.vec.size(); ++i) {
        copy_with_double_round(this->vec[i], rhs.vec[i]);
    }
    return *this;
}

VecND_LC VecND_LC::operator*(const LongComplex &rhs) const {
    VecND_LC tmp((int) vec.size());
    for (int i = 0; i < vec.size(); ++i) {
        move_with_double_round(tmp.vec[i], this->vec[i] * rhs);
    }
    return VecND_LC{tmp};
}

VecND_LC &VecND_LC::operator*=(const LongComplex &rhs) {
    for (int i = 0; i < vec.size(); ++i) {
        move_with_double_round(this->vec[i], this->vec[i] * rhs);
    }
    return *this;
}

void VecND_LC::print() const {
    std::cout << '(';
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1)
            std::cout << ", ";
    }
    std::cout << ")\n";
}

LongComplex &VecND_LC::operator[](int index) {
    if (index < this->vec.size()) {
        return vec[index];
    }
    throw std::length_error("Vector: Invalid index");
}

const LongComplex &VecND_LC::operator[](int index) const {
    if (index < this->vec.size()) {
        return vec[index];
    }
    throw std::length_error("Vector: Invalid index");
}

int VecND_LC::size() const {
    return (int) vec.size();
}

VecND_LC::VecND_LC(VecND_LC &&el) noexcept {
    vec = std::move(el.vec);
}

VecND_LC &VecND_LC::operator=(VecND_LC &&rhs) noexcept {
    if (this == &rhs)
        return *this;
    vec = std::move(rhs.vec);
    return *this;
}

