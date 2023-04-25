#ifndef VECND_LN_H
#define VECND_LN_H

#include "iostream"
#include "vector"
#include "../LongNumber/LongNumber.h"

class VecND_LN {
    friend class Mat2D_LN;

private:
    std::vector<LongNumber> vec;
public:
    VecND_LN();

    explicit VecND_LN(int x_);

    VecND_LN(const VecND_LN &el);

    VecND_LN(VecND_LN &&el) noexcept;

    void print();

    LongNumber &operator[](int index);

    const LongNumber &operator[](int index) const;

    VecND_LN operator+(const VecND_LN &rhs) const;

    VecND_LN operator-(const VecND_LN &rhs) const;

    VecND_LN operator*(const LongNumber &rhs) const;

    VecND_LN &operator*=(const LongNumber &rhs);

    VecND_LN &operator=(const VecND_LN &rhs);

    VecND_LN &operator=(VecND_LN &&rhs) noexcept;

    [[nodiscard]] int size() const;
};


#endif
