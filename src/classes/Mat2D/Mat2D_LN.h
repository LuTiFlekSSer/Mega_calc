#ifndef MAT2D_LN_H
#define MAT2D_LN_H

#include "iostream"
#include "vector"
#include "src/classes/VecND/VecND_LN.h"
#include "tuple"
#include "algorithm"

class Mat2D_LN {
private:
    std::vector<VecND_LN> mat;

    [[nodiscard]] std::tuple<int, int, LongNumber> max_elem(const Mat2D_LN &matrix, int index) const;

    [[nodiscard]] std::tuple<Mat2D_LN, Mat2D_LN, Mat2D_LN, Mat2D_LN> lu_decomposition() const;

public:

    Mat2D_LN(int x_, int y_);

    explicit Mat2D_LN(int x_);

    Mat2D_LN(const Mat2D_LN &el);

    Mat2D_LN(Mat2D_LN &&el) noexcept;

    Mat2D_LN();

    void print() const;

    Mat2D_LN operator+(const Mat2D_LN &rhs);

    Mat2D_LN operator-(const Mat2D_LN &rhs);

    Mat2D_LN operator*(const LongNumber &rhs);

    Mat2D_LN operator*(const Mat2D_LN &rhs);

    VecND_LN operator*(const VecND_LN &rhs);

    Mat2D_LN &operator=(const Mat2D_LN &rhs);

    Mat2D_LN &operator=(Mat2D_LN &&rhs) noexcept;

    Mat2D_LN &operator=(const VecND_LN &rhs);

    Mat2D_LN &operator=(VecND_LN &&rhs) noexcept;

    [[nodiscard]] std::tuple<VecND_LN, Mat2D_LN> solve(const VecND_LN &b) const;

    [[nodiscard]] Mat2D_LN T() const;

    [[nodiscard]] LongNumber det() const;

    [[nodiscard]] LongNumber rang() const;

    [[nodiscard]] Mat2D_LN inv() const;

    VecND_LN &operator[](int index);

    const VecND_LN &operator[](int index) const;

    [[nodiscard]] int size() const;
};

Mat2D_LN eye(int size);

void print_solve(const std::tuple<VecND_LN, Mat2D_LN> &xc);

#endif
