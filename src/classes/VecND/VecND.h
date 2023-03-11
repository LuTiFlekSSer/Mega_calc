#ifndef PRACTIC_5_VECND_H
#define PRACTIC_5_VECND_H

#include "iostream"
#include "vector"
#include "../LongNumber/LongNumber.h"

class VecND {
    friend class Mat2D;

private:
    std::vector<LongNumber> vec;
public:
    VecND();

    explicit VecND(int x_);

    VecND(const VecND &el);

    VecND(VecND &&el) noexcept;

    void print();

    LongNumber &operator[](int index);

    VecND operator+(const VecND &rhs) const;

    VecND operator-(const VecND &rhs) const;

    VecND operator*(const LongNumber &rhs) const;

    VecND &operator*=(const LongNumber &rhs);

    VecND &operator=(const VecND &rhs);

    VecND &operator=(VecND &&rhs) noexcept;

    int size();
};


#endif
