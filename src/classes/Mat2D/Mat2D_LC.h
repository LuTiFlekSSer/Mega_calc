#ifndef MAT2D_LC_H
#define MAT2D_LC_H

#include "iostream"
#include "vector"
#include "src/classes/VecND/VecND_LC.h"
#include "src/classes/Mat2D/Mat2D_LN.h"
#include "tuple"
#include "algorithm"

class Mat2D_LC {
private:
    std::vector<VecND_LC> mat;

    std::tuple<int, int, LongComplex> max_elem(Mat2D_LC &matrix, int index);

    std::tuple<Mat2D_LC, Mat2D_LC, Mat2D_LC, Mat2D_LC> lu_decomposition();

public:
    Mat2D_LC(int x_, int y_);

    explicit Mat2D_LC(int x_);

    Mat2D_LC(const Mat2D_LC &el);

    Mat2D_LC(Mat2D_LC &&el) noexcept;

    Mat2D_LC();

    void print();

    Mat2D_LC operator+(const Mat2D_LC &rhs);

    Mat2D_LC operator-(const Mat2D_LC &rhs);

    Mat2D_LC operator*(const LongComplex &rhs);

    Mat2D_LC operator*(const Mat2D_LC &rhs);

    VecND_LC operator*(const VecND_LC &rhs);

    Mat2D_LC &operator=(const Mat2D_LC &rhs);

    Mat2D_LC &operator=(Mat2D_LC &&rhs) noexcept;

    Mat2D_LC &operator=(const VecND_LC &rhs);

    Mat2D_LC &operator=(VecND_LC &&rhs) noexcept;

    std::tuple<VecND_LC, Mat2D_LC> solve(VecND_LC &b);

    Mat2D_LC T();

    LongComplex det();

    VecND_LC &operator[](int index);

    const VecND_LC &operator[](int index) const;

    [[nodiscard]] int size() const;
};

Mat2D_LC c_eye(int size);

void print_solve(std::tuple<VecND_LC, Mat2D_LC> xc);

#endif
