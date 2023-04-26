#ifndef VECND_LC_H
#define VECND_LC_H

#include "iostream"
#include "vector"
#include "../LongComplex/LongComplex.h"

class VecND_LC {
    friend class Mat2D_LC;

private:
    std::vector<LongComplex> vec;
public:
    VecND_LC();

    explicit VecND_LC(int x_);

    VecND_LC(const VecND_LC &el);

    VecND_LC(VecND_LC &&el) noexcept;

    void print() const;

    LongComplex &operator[](int index);

    const LongComplex &operator[](int index) const;

    VecND_LC operator+(const VecND_LC &rhs) const;

    VecND_LC operator-(const VecND_LC &rhs) const;

    VecND_LC operator*(const LongComplex &rhs) const;

    VecND_LC &operator*=(const LongComplex &rhs);

    VecND_LC &operator=(const VecND_LC &rhs);

    VecND_LC &operator=(VecND_LC &&rhs) noexcept;

    [[nodiscard]] int size() const;
};


#endif
