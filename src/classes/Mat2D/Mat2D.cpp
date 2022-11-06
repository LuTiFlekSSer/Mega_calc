#include "Mat2D.h"
#include "cmath"

double eps = std::pow(10, -10);

Mat2D::Mat2D(int x_, int y_) {
    mat.resize(x_);
    for (int i = 0; i < x_; ++i) {
        mat[i] = VecND(y_);
    }
}

void Mat2D::print() {
    std::cout << '(';
    for (int i = 0; i < mat.size(); ++i) {
        std::cout << '(';
        for (int j = 0; j < mat[0].vec.size(); ++j) {
            std::cout << mat[i][j];
            if (j != mat[0].vec.size() - 1)
                std::cout << ", ";
        }
        if (i < mat.size() - 1)
            std::cout << ")\n ";
    }
    std::cout << "))\n";
}

VecND &Mat2D::operator[](int index) {
    if (index < this->mat.size()) {
        return mat[index];
    }
    throw std::length_error("Invalid index");
}

Mat2D Mat2D::operator+(const Mat2D &rhs) {
    if (this->mat.size() == rhs.mat.size() and this->mat[0].vec.size() == rhs.mat[0].vec.size()) {
        Mat2D tmp((int) mat.size(), (int) mat[0].vec.size());
        for (int i = 0; i < mat.size(); ++i) {
            for (int j = 0; j < mat[0].vec.size(); ++j) {
                tmp[i][j] = mat[i][j] + rhs.mat[i].vec[j];
            }
        }
        return Mat2D(tmp);
    }
    throw std::length_error("Different dimensions of matrix");
}

Mat2D::Mat2D(const Mat2D &el) {
    mat.resize(el.mat.size());
    for (int i = 0; i < mat.size(); ++i) {
        mat[i] = el.mat[i];
    }
}

Mat2D &Mat2D::operator=(const Mat2D &rhs) {
    mat.resize(rhs.mat.size());
    for (int i = 0; i < mat.size(); ++i) {
        mat[i] = rhs.mat[i];
    }
    return *this;
}

Mat2D Mat2D::operator*(const Mat2D &rhs) {
    if (this->mat[0].vec.size() == rhs.mat.size()) {
        Mat2D tmp((int) mat.size(), (int) rhs.mat[0].vec.size());
        for (int i = 0; i < mat.size(); ++i) {
            for (int j = 0; j < rhs.mat[0].vec.size(); ++j) {
                for (int k = 0; k < mat[0].vec.size(); ++k) {
                    tmp[i][j] += mat[i][k] * rhs.mat[k].vec[j];
                }
            }
        }
        return Mat2D(tmp);
    }
    throw std::length_error("Multiplication is not possible");
}

Mat2D Mat2D::T() {
    Mat2D tmp((int) this->mat[0].vec.size(), (int) this->mat.size());
    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat[0].vec.size(); ++j) {
            tmp[j][i] = this->mat[i][j];
        }
    }
    return Mat2D(tmp);
}

double determ(Mat2D &matrix) {
    if (matrix.mat.size() == 1)
        return matrix[0][0];
    else if (matrix.mat.size() == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    double otvet = 0;
    for (int i = 0; i < matrix.mat.size(); ++i) {
        Mat2D minor((int) matrix.mat.size() - 1, (int) matrix.mat.size() - 1);
        int x = 0, y = 0;
        for (int j = 1; j < matrix.mat.size(); ++j) {
            for (int k = 0; k < matrix.mat[0].vec.size(); ++k) {
                if (k == i)
                    continue;
                minor[x][y++] = matrix[j][k];
            }
            y = 0;
            ++x;
        }
        otvet += std::pow(-1, i) * matrix[0][i] * determ(minor);
    }
    return otvet;
}

double Mat2D::det() {
    if (this->mat.size() == this->mat[0].vec.size())
        return determ(*this);
    throw std::length_error("The matrix is not square");
}

VecND Mat2D::operator*(const VecND &rhs) {
    if (this->mat[0].vec.size() == rhs.vec.size()) {
        Mat2D tmp(1, (int) rhs.vec.size()), rhs_mat(1, (int) rhs.vec.size());
        rhs_mat[0] = rhs;
        tmp = *this * rhs_mat.T();
        return VecND(tmp.T()[0]);
    }
    throw std::length_error("Multiplication is not possible");
}

Mat2D &Mat2D::operator=(const VecND &rhs) {
    mat.resize(1);
    mat[0] = rhs;
    return *this;
}

Mat2D::Mat2D() {

}

Mat2D Mat2D::operator*(const double &rhs) {
    Mat2D tmp(*this);
    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat[0].vec.size(); ++j) {
            tmp[i][j] *= rhs;
        }
    }
    return Mat2D(tmp);
}

Mat2D eye(int size) {
    Mat2D tmp(size, size);
    for (int i = 0; i < size; ++i) {
        tmp[i][i] = 1;
    }
    return Mat2D(tmp);
}

VecND Mat2D::solve(VecND &cof) {
    if (this->mat.size() == this->mat[0].vec.size() and this->mat.size() == cof.vec.size()) {
        VecND tmp((int) cof.vec.size());
        double d = determ(*this);
        if (d == 0)
            throw std::logic_error("Determinant is zero");
        for (int i = 0; i < mat.size(); ++i) {
            Mat2D add_mat(*this);
            for (int j = 0; j < mat.size(); ++j) {
                add_mat[j][i] = cof[j];
            }
            tmp[i] = determ(add_mat) / d;
        }
        return VecND(tmp);
    }
    throw std::length_error("Matrix is not square or does not match the size of the vector");
}

std::tuple<int, int, double> max_elem(Mat2D &matrix, int index) {
    int x = index, y = index;
    double max = matrix[index][index];
    for (int i = index; i < std::min(matrix.mat.size(), matrix.mat[0].vec.size()); ++i) {
        for (int j = index; j < std::min(matrix.mat.size(), matrix.mat[0].vec.size()); ++j) {
            if (std::abs(matrix[i][j]) > std::abs(max)) {
                x = i;
                y = j;
                max = matrix[i][j];
            }
        }
    }
    return std::make_tuple(x, y, max);
}

std::tuple<Mat2D, Mat2D, Mat2D, Mat2D> Mat2D::lu_decomposition() {
    Mat2D u(*this);
    Mat2D p = eye((int) this->mat.size()), q = eye((int) this->mat[0].vec.size()), l((int) this->mat.size());
    for (int i = 0; i < std::min(this->mat.size(), this->mat[0].vec.size()); ++i) {
        auto maximum = max_elem(u, i);
        int index_row = std::get<0>(maximum), index_column = std::get<1>(maximum);
        double elem = std::get<2>(maximum);
        if (index_row != i) {
            std::swap(u[i], u[index_row]);
            std::swap(p[i], p[index_row]);
            std::swap(l[i], l[index_row]);
        }
        if (index_column != i) {
            for (int j = 0; j < this->mat.size(); ++j) {
                std::swap(u[j][i], u[j][index_column]);
                if (j < this->mat[0].vec.size())
                    std::swap(q[j][i], q[j][index_column]);
                std::swap(l[j][i], l[j][index_column]);
            }
        }
        if (std::abs(elem) > eps) {
            for (int j = i + 1; j < this->mat.size(); ++j) {
                l[j][i] = u[j][i] / u[i][i];
                VecND v1((int) this->mat[0].vec.size());
                for (int k = 0; k < this->mat[0].vec.size(); ++k)
                    v1[k] = u[j][k] - u[i][k] * u[j][i] / u[i][i];
                u[j] = v1;
            }
        }
    }
    for (int i = 0; i < this->mat.size(); ++i) {
        l[i][i] = 1;
    }
    return std::make_tuple(Mat2D(p), Mat2D(l), Mat2D(u), Mat2D(q));
}

Mat2D::Mat2D(int x_) {
    mat.resize(x_);
    for (int i = 0; i < x_; ++i) {
        mat[i] = VecND(x_);
    }
}


