#include "VecND.h"

VecND::VecND(int x_) {
    for (int i = 0; i < x_; ++i) {
        vec.push_back(0);
    }
}

VecND::VecND() = default;

VecND::VecND(const VecND &el) {
    vec = el.vec;
}

VecND VecND::operator+(const VecND &rhs) const {
    if (this->vec.size() == rhs.vec.size()) {
        VecND tmp((int) rhs.vec.size());
        for (int i = 0; i < rhs.vec.size(); ++i) {
            tmp.vec[i] = this->vec[i] + rhs.vec[i];
        }
        return VecND{tmp};
    }
    throw std::length_error("Different length of vectors");
}

VecND VecND::operator-(const VecND &rhs) const {
    if (this->vec.size() == rhs.vec.size()) {
        VecND tmp((int) rhs.vec.size());
        for (int i = 0; i < rhs.vec.size(); ++i) {
            tmp.vec[i] = this->vec[i] - rhs.vec[i];
        }
        return VecND{tmp};
    }
    throw std::length_error("Different length of vectors");
}

VecND &VecND::operator=(const VecND &rhs) = default;

VecND VecND::operator*(const double &rhs) const {
    VecND tmp((int) vec.size());
    for (int i = 0; i < vec.size(); ++i) {
        tmp.vec[i] = this->vec[i] * rhs;
    }
    return VecND{tmp};
}

VecND &VecND::operator*=(const double &rhs) {
    for (int i = 0; i < vec.size(); ++i) {
        this->vec[i] *= rhs;
    }
    return *this;
}

void VecND::print() {
    std::cout << '(';
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1)
            std::cout << ", ";
    }
    std::cout << ")\n";
}

double &VecND::operator[](int index) {
    if (index < this->vec.size()) {
        return vec[index];
    }
    throw std::length_error("Invalid index");
}

int VecND::size() {
    return (int) vec.size();
}

