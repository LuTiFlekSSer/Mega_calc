#include "Mat2D.h"
#include "cmath"


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
    if (mat.empty())
        std::cout << '(';
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
        return Mat2D{tmp};
    }
    throw std::length_error("Different dimensions of matrix");
}

Mat2D Mat2D::operator-(const Mat2D &rhs) {
    if (this->mat.size() == rhs.mat.size() and this->mat[0].vec.size() == rhs.mat[0].vec.size()) {
        Mat2D tmp((int) mat.size(), (int) mat[0].vec.size());
        for (int i = 0; i < mat.size(); ++i) {
            for (int j = 0; j < mat[0].vec.size(); ++j) {
                tmp[i][j] = mat[i][j] - rhs.mat[i].vec[j];
            }
        }
        return Mat2D{tmp};
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
        return Mat2D{tmp};
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
    return Mat2D{tmp};
}

LongNumber Mat2D::det() {
    if (this->mat.size() == this->mat[0].vec.size()) {
        auto pluq = (*this).lu_decomposition();
        VecND liner_p((int) std::get<0>(pluq).mat.size());
        for (int i = 0; i < std::get<0>(pluq).mat.size(); ++i) {
            for (int j = 0; j < std::get<0>(pluq).mat.size(); ++j) {
                if (std::get<0>(pluq)[i][j] == LongNumber(1)) {
                    liner_p[i] = LongNumber(j);
                    break;
                }
            }
        }
        VecND liner_q((int) std::get<3>(pluq).mat.size());
        for (int i = 0; i < std::get<3>(pluq).mat.size(); ++i) {
            for (int j = 0; j < std::get<3>(pluq).mat.size(); ++j) {
                if (std::get<3>(pluq)[i][j] == LongNumber(1)) {
                    liner_q[i] = LongNumber(j);
                    break;
                }
            }
        }
        int res = 0;
        for (int i = 0; i < liner_p.vec.size(); ++i) {
            for (int j = i + 1; j < liner_p.vec.size(); ++j) {
                if (liner_p[i] > liner_p[j])
                    ++res;
            }
        }
        for (int i = 0; i < liner_q.vec.size(); ++i) {
            for (int j = i + 1; j < liner_q.vec.size(); ++j) {
                if (liner_q[i] > liner_q[j])
                    ++res;
            }
        }
        LongNumber determ(1);
        for (int i = 0; i < std::get<2>(pluq).mat.size(); ++i) {
            determ *= std::get<2>(pluq)[i][i];
        }
        return determ * LongNumber(pow(-1, res));
    }
    throw std::length_error("The matrix is not square");
}

VecND Mat2D::operator*(const VecND &rhs) {
    if (this->mat[0].vec.size() == rhs.vec.size()) {
        Mat2D tmp(1, (int) rhs.vec.size()), rhs_mat(1, (int) rhs.vec.size());
        rhs_mat[0] = rhs;
        tmp = *this * rhs_mat.T();
        return VecND{tmp.T()[0]};
    }
    throw std::length_error("Multiplication is not possible");
}

Mat2D &Mat2D::operator=(const VecND &rhs) {
    mat.resize(1);
    mat[0] = rhs;
    return *this;
}

Mat2D::Mat2D() = default;

Mat2D Mat2D::operator*(const LongNumber &rhs) {
    Mat2D tmp(*this);
    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat[0].vec.size(); ++j) {
            tmp[i][j] *= rhs;
        }
    }
    return Mat2D{tmp};
}

Mat2D eye(int size) {
    Mat2D tmp(size, size);
    for (int i = 0; i < size; ++i) {
        tmp[i][i] = LongNumber(1);
    }
    return Mat2D{tmp};
}

std::tuple<VecND, Mat2D> Mat2D::solve(VecND &b) {
    if (this->mat.size() == b.vec.size()) {
        auto pluq = (*this).lu_decomposition();
        VecND pb = std::get<0>(pluq) * b;
        Mat2D c((int) std::get<2>(pluq).mat[0].vec.size(), (int) std::get<2>(pluq).mat[0].vec.size() - (int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()));
        for (int i = (int) std::get<2>(pluq).mat[0].vec.size() - (int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()) - 1; i >= 0; --i) {
            c[i + (int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size())][i] = LongNumber(1);
        }
        VecND y((int) std::get<2>(pluq).mat.size());
        Mat2D yc((int) std::get<2>(pluq).mat.size(), (int) std::get<2>(pluq).mat[0].vec.size() - (int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()));
        for (int i = 0; i < std::get<2>(pluq).mat.size(); ++i) {
            LongNumber sum = LongNumber::zero;
            for (int j = 0; j < i; ++j) {
                sum += y[j] * std::get<1>(pluq)[i][j];
            }
            y[i] = pb[i] - sum;
        }
        int index_first_not_null = -1;
        for (int i = (int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()) - 1; i >= 0; --i) {
            if (abs(std::get<2>(pluq)[i][i]) < LongNumber::eps) {
                if (abs(y[i]) > LongNumber::eps)
                    return std::make_tuple(VecND(0), Mat2D(0));
            } else {
                index_first_not_null = i;
                break;
            }
        }
        for (int i = (int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()) - 1; i < std::get<2>(pluq).mat.size(); ++i)
            if (abs(std::get<2>(pluq)[i][(int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()) - 1]) < LongNumber::eps and abs(y[i]) > LongNumber::eps)
                return std::make_tuple(VecND(0), Mat2D(0));
        VecND x((int) std::get<2>(pluq).mat[0].vec.size());
        for (int i = index_first_not_null; i >= 0; --i) {
            LongNumber sum(0);
            for (int j = index_first_not_null; j > i; --j) {
                sum += x[j] * std::get<2>(pluq)[i][j];
            }
            if (abs((y[i] - sum) / std::get<2>(pluq)[i][i]) > LongNumber::eps)
                x[i] = (y[i] - sum) / std::get<2>(pluq)[i][i];
        }
        for (int i = 0; i < std::get<2>(pluq).mat[0].vec.size() -
                            std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()); ++i) {
            for (int j = (int) std::get<2>(pluq).mat.size() - 1; j >= 0; --j) {
                LongNumber sum(0);
                for (int k = (int) std::get<2>(pluq).mat[0].vec.size() - 1; k > j; --k) {
                    sum += std::get<2>(pluq)[j][k] * c[k][i];
                }
                //хуйня! зато какая ↓
                if (abs(std::get<2>(pluq)[j][j]) > LongNumber::eps) {
                    c[j][i] = (-sum) / std::get<2>(pluq)[j][j];
                    if (abs(c[j][i]) < LongNumber::eps)
                        c[j][i] = LongNumber::zero;
                } else {
                    if (abs(sum) < LongNumber::eps)
                        c[j][i] = LongNumber::zero;
                    else {
                        c[j][i] = LongNumber(1);
                        c[(int) std::get<2>(pluq).mat.size() + i][i] = LongNumber::zero;
                    }
                }
            }
        }
        if (index_first_not_null == std::max(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()) - 1)
            return std::make_tuple(VecND(std::get<3>(pluq) * x), Mat2D(0));
        else
            return std::make_tuple(VecND(std::get<3>(pluq) * x), Mat2D(std::get<3>(pluq) * c));
    }
    throw std::length_error("Matrix does not match the size of the vector");
}

std::tuple<int, int, LongNumber> Mat2D::max_elem(Mat2D &matrix, int index) {
    int x = index, y = index;
    LongNumber max = matrix[index][index];
    for (int i = index; i < matrix.mat.size(); ++i) {
        for (int j = index; j < matrix.mat[0].vec.size(); ++j) {
            if (abs(matrix[i][j]) > abs(max)) {
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
        LongNumber elem = std::get<2>(maximum);
        if (index_row != i) {
            std::swap(u[i], u[index_row]);
            std::swap(p[i], p[index_row]);
            std::swap(l[i], l[index_row]);
        }
        if (index_column != i) {
            for (int j = 0; j < this->mat.size(); ++j) {
                std::swap(u[j][i], u[j][index_column]);
            }
            for (int j = 0; j < this->mat[0].vec.size(); ++j) {
                std::swap(q[j][i], q[j][index_column]);
            }
        }
        if (abs(elem) > LongNumber::eps) {
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
        l[i][i] = LongNumber(1);
    }
    return std::make_tuple(Mat2D(p), Mat2D(l), Mat2D(u), Mat2D(q));
}

Mat2D::Mat2D(int x_) {
    mat.resize(x_);
    for (int i = 0; i < x_; ++i) {
        mat[i] = VecND(x_);
    }
}

int Mat2D::size() {
    return (int) mat.size();
}

void print_solve(std::tuple<VecND, Mat2D> xc) {
    if (std::get<0>(xc).size() == 0)
        std::cout << "No solution\n";
    else if (std::get<1>(xc).size() == 0 or std::get<1>(xc)[0].size() == 0) {
        int hsize = std::get<0>(xc).size() / 2;
        for (int i = 0; i < std::get<0>(xc).size(); ++i) {
            if (i != hsize)
                std::cout << "    |" << std::get<0>(xc)[i] << "|\n";
            else
                std::cout << "X = |" << std::get<0>(xc)[i] << "|\n";
        }
    } else {
        int hsize = std::get<0>(xc).size() / 2;
        for (int i = 0; i < std::get<0>(xc).size(); ++i) {
            if (i != hsize) {
                std::cout << "    |" << std::get<0>(xc)[i] << " ";
                for (int j = 0; j < std::get<1>(xc)[0].size(); ++j) {
                    if (j < std::get<1>(xc)[0].size() - 1)
                        std::cout << "+ (" << std::get<1>(xc)[i][j] << ") * C" << j + 1 << ' ';
                    else
                        std::cout << "+ (" << std::get<1>(xc)[i][j] << ") * C" << j + 1 << "|\n";
                }
            } else {
                std::cout << "X = |" << std::get<0>(xc)[i] << " ";
                for (int j = 0; j < std::get<1>(xc)[0].size(); ++j) {
                    if (j < std::get<1>(xc)[0].size() - 1)
                        std::cout << "+ (" << std::get<1>(xc)[i][j] << ") * C" << j + 1 << ' ';
                    else
                        std::cout << "+ (" << std::get<1>(xc)[i][j] << ") * C" << j + 1 << "|\n";
                }
            }
        }
    }
}

