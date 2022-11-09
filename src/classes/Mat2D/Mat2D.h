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

    std::tuple<int, int, double> max_elem(Mat2D &matrix, int index);

    std::tuple<Mat2D, Mat2D, Mat2D, Mat2D> lu_decomposition();

public:
    Mat2D(int x_, int y_x);

    explicit Mat2D(int x_);

    Mat2D(const Mat2D &el);

    Mat2D();

    void print();

    Mat2D operator+(const Mat2D &rhs);

    Mat2D operator*(const double &rhs);

    Mat2D operator*(const Mat2D &rhs);

    VecND operator*(const VecND &rhs);

    Mat2D &operator=(const Mat2D &rhs);

    Mat2D &operator=(const VecND &rhs);

    std::tuple<VecND, Mat2D> solve(VecND &b);

    Mat2D T();

    double det();

    VecND &operator[](int index);

    int size();
};

Mat2D eye(int size);

#endif
