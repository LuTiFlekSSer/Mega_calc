#ifndef PRACTIC_5_MAT2D_H
#define PRACTIC_5_MAT2D_H

#include "iostream"
#include "vector"
#include "../VecND/VecND.h"
#include "tuple"
#include "algorithm"

class Mat2D {
private:
    std::vector<VecND> mat;

    std::tuple<int, int, LongNumber> max_elem(Mat2D &matrix, int index);

    std::tuple<Mat2D, Mat2D, Mat2D, Mat2D> lu_decomposition();

public:
    Mat2D(int x_, int y_x);

    explicit Mat2D(int x_);

    Mat2D(const Mat2D &el);

    Mat2D(Mat2D &&el) noexcept;

    Mat2D();

    void print();

    Mat2D operator+(const Mat2D &rhs);

    Mat2D operator-(const Mat2D &rhs);

    Mat2D operator*(const LongNumber &rhs);

    Mat2D operator*(const Mat2D &rhs);

    VecND operator*(const VecND &rhs);

    Mat2D &operator=(const Mat2D &rhs);

    Mat2D &operator=(Mat2D &&rhs) noexcept;

    Mat2D &operator=(const VecND &rhs);

    Mat2D &operator=(VecND &&rhs) noexcept;

    std::tuple<VecND, Mat2D> solve(VecND &b);

    Mat2D T();

    LongNumber det();

    VecND &operator[](int index);

    int size();
};

Mat2D eye(int size);

void print_solve(std::tuple<VecND, Mat2D> xc);

#endif
