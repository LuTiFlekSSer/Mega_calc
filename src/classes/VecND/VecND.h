#ifndef PRACTIC_5_VECND_H
#define PRACTIC_5_VECND_H

#include "iostream"
#include "vector"

class VecND {
    friend class Mat2D;

private:
    std::vector<double> vec;
public:
    VecND();

    explicit VecND(int x_);

    VecND(const VecND &el);

    void print();

    double &operator[](int index);

    VecND operator+(const VecND &rhs) const;

    VecND operator*(const double &rhs) const;

    VecND &operator*=(const double &rhs);

    VecND &operator=(const VecND &rhs);

    int size();
};


#endif
