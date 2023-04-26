#include "Mat2D_LC.h"
#include "cmath"


Mat2D_LC::Mat2D_LC(int x_, int y_) {
    mat.resize(x_);
    for (int i = 0; i < x_; ++i) {
        mat[i] = VecND_LC(y_);
    }
}

void Mat2D_LC::print() const {
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

VecND_LC &Mat2D_LC::operator[](int index) {
    if (index < this->mat.size()) {
        return mat[index];
    }
    throw std::length_error("Matrix: invalid index");
}

const VecND_LC &Mat2D_LC::operator[](int index) const {
    if (index < this->mat.size()) {
        return mat[index];
    }
    throw std::length_error("Matrix: invalid index");
}

Mat2D_LC Mat2D_LC::operator+(const Mat2D_LC &rhs) {
    if (this->mat.size() == rhs.mat.size() and this->mat[0].vec.size() == rhs.mat[0].vec.size()) {
        Mat2D_LC tmp((int) mat.size(), (int) mat[0].vec.size());
        for (int i = 0; i < mat.size(); ++i) {
            for (int j = 0; j < mat[0].vec.size(); ++j) {
                move_with_double_round(tmp[i][j], mat[i][j] + rhs.mat[i].vec[j]);
            }
        }
        return Mat2D_LC{tmp};
    }
    throw std::length_error("Incorrect addition: different dimensions of matrix");
}

Mat2D_LC Mat2D_LC::operator-(const Mat2D_LC &rhs) {
    if (this->mat.size() == rhs.mat.size() and this->mat[0].vec.size() == rhs.mat[0].vec.size()) {
        Mat2D_LC tmp((int) mat.size(), (int) mat[0].vec.size());
        for (int i = 0; i < mat.size(); ++i) {
            for (int j = 0; j < mat[0].vec.size(); ++j) {
                move_with_double_round(tmp[i][j], mat[i][j] - rhs.mat[i].vec[j]);
            }
        }
        return Mat2D_LC{tmp};
    }
    throw std::length_error("Incorrect subtraction: different dimensions of matrix");
}

Mat2D_LC::Mat2D_LC(const Mat2D_LC &el) {
    mat.resize(el.mat.size());
    for (int i = 0; i < mat.size(); ++i) {
        mat[i] = el.mat[i];
    }
}

Mat2D_LC &Mat2D_LC::operator=(const Mat2D_LC &rhs) {
    mat.resize(rhs.mat.size());
    for (int i = 0; i < mat.size(); ++i) {
        mat[i] = rhs.mat[i];
    }
    return *this;
}

Mat2D_LC Mat2D_LC::operator*(const Mat2D_LC &rhs) {
    if (this->mat[0].vec.size() == rhs.mat.size()) {
        Mat2D_LC tmp((int) mat.size(), (int) rhs.mat[0].vec.size());
        for (int i = 0; i < mat.size(); ++i) {
            for (int j = 0; j < rhs.mat[0].vec.size(); ++j) {
                for (int k = 0; k < mat[0].vec.size(); ++k) {
                    move_with_double_round(tmp[i][j], tmp[i][j] + mat[i][k] * rhs.mat[k].vec[j]);
                }
            }
        }
        return Mat2D_LC{tmp};
    }
    throw std::length_error("Incorrect multiplication: different matrix sizes");
}

Mat2D_LC Mat2D_LC::T() const {
    Mat2D_LC tmp((int) this->mat[0].vec.size(), (int) this->mat.size());
    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat[0].vec.size(); ++j) {
            copy_with_double_round(tmp[j][i], this->mat[i][j]);
        }
    }
    return Mat2D_LC{tmp};
}

LongComplex rec_det(const Mat2D_LC &m) {
    if (m.size() == 1) {
        return m[0][0];
    } else if (m.size() == 2) {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    } else {
        LongComplex result;
        for (int i = 0; i < m.size(); ++i) {
            Mat2D_LC minor(m.size() - 1, m.size() - 1);
            int x = 0, y = 0;
            for (int j = 1; j < m.size(); ++j) {
                for (int k = 0; k < m[0].size(); ++k) {
                    if (k == i)
                        continue;
                    copy_with_double_round(minor[x][y++], m[j][k]);
                }
                y = 0;
                ++x;
            }
            move_with_double_round(result, result + rec_det(minor) * pow(-LongComplex::one, LongComplex(i)) * m[0][i]);
        }
        return result;
    }
}

LongComplex Mat2D_LC::det() const {
    if (this->mat.size() == this->mat[0].vec.size()) {
        if (this->mat.size() < 8) {
            return rec_det(*this);
        }
        auto pluq = (*this).lu_decomposition();
        VecND_LC liner_p((int) std::get<0>(pluq).mat.size());
        for (int i = 0; i < std::get<0>(pluq).mat.size(); ++i) {
            for (int j = 0; j < std::get<0>(pluq).mat.size(); ++j) {
                if (std::get<0>(pluq)[i][j] == LongComplex(1)) {
                    liner_p[i] = LongComplex(j);
                    break;
                }
            }
        }
        VecND_LC liner_q((int) std::get<3>(pluq).mat.size());
        for (int i = 0; i < std::get<3>(pluq).mat.size(); ++i) {
            for (int j = 0; j < std::get<3>(pluq).mat.size(); ++j) {
                if (std::get<3>(pluq)[i][j] == LongComplex(1)) {
                    liner_q[i] = LongComplex(j);
                    break;
                }
            }
        }
        int res = 0;
        for (int i = 0; i < liner_p.vec.size(); ++i) {
            for (int j = i + 1; j < liner_p.vec.size(); ++j) {
                if (abs(liner_p[i]) > abs(liner_p[j]))
                    ++res;
            }
        }
        for (int i = 0; i < liner_q.vec.size(); ++i) {
            for (int j = i + 1; j < liner_q.vec.size(); ++j) {
                if (abs(liner_q[i]) > abs(liner_q[j]))
                    ++res;
            }
        }
        LongComplex determ(1);
        for (int i = 0; i < std::get<2>(pluq).mat.size(); ++i) {
            move_with_double_round(determ, determ * std::get<2>(pluq)[i][i]);
        }
        return determ * LongComplex(pow(-1, res));
    }
    throw std::length_error("Incorrect determinant: the matrix is not square");
}

VecND_LC Mat2D_LC::operator*(const VecND_LC &rhs) {
    if (this->mat[0].vec.size() == rhs.vec.size()) {
        Mat2D_LC tmp(1, (int) rhs.vec.size()), rhs_mat(1, (int) rhs.vec.size());
        rhs_mat[0] = rhs;
        tmp = *this * rhs_mat.T();
        return VecND_LC{tmp.T()[0]};
    }
    throw std::length_error("Incorrect multiplication: different matrix and vector sizes");
}

Mat2D_LC &Mat2D_LC::operator=(const VecND_LC &rhs) {
    mat.resize(1);
    mat[0] = rhs;
    return *this;
}

Mat2D_LC::Mat2D_LC() = default;

Mat2D_LC Mat2D_LC::operator*(const LongComplex &rhs) {
    Mat2D_LC tmp(*this);
    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat[0].vec.size(); ++j) {
            move_with_double_round(tmp[i][j], tmp[i][j] * rhs);
        }
    }
    return Mat2D_LC{tmp};
}

Mat2D_LC c_eye(int size) {
    Mat2D_LC tmp(size, size);
    for (int i = 0; i < size; ++i) {
        tmp[i][i] = LongComplex(1);
    }
    return Mat2D_LC{tmp};
}

std::tuple<VecND_LC, Mat2D_LC> Mat2D_LC::solve(const VecND_LC &b) const {
    if (this->mat.size() == b.vec.size()) {
        auto pluq = (*this).lu_decomposition();
        VecND_LC pb = std::get<0>(pluq) * b;
        Mat2D_LC c((int) std::get<2>(pluq).mat[0].vec.size(), (int) std::get<2>(pluq).mat[0].vec.size() - (int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()));
        for (int i = (int) std::get<2>(pluq).mat[0].vec.size() - (int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()) - 1; i >= 0; --i) {
            c[i + (int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size())][i] = LongComplex(1);
        }
        VecND_LC y((int) std::get<2>(pluq).mat.size());
        Mat2D_LC yc((int) std::get<2>(pluq).mat.size(), (int) std::get<2>(pluq).mat[0].vec.size() - (int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()));
        for (int i = 0; i < std::get<2>(pluq).mat.size(); ++i) {
            LongComplex sum = LongComplex::czero;
            for (int j = 0; j < i; ++j) {
                move_with_double_round(sum, sum + y[j] * std::get<1>(pluq)[i][j]);
            }
            move_with_double_round(y[i], pb[i] - sum);
        }
        int index_first_not_null = -1;
        for (int i = (int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()) - 1; i >= 0; --i) {
            if (abs(std::get<2>(pluq)[i][i]) < LongNumber::eps) {
                if (abs(y[i]) > LongNumber::eps)
                    return std::make_tuple(VecND_LC(0), Mat2D_LC(0));
            } else {
                index_first_not_null = i;
                break;
            }
        }
        for (int i = (int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()) - 1; i < std::get<2>(pluq).mat.size(); ++i)
            if (abs(std::get<2>(pluq)[i][(int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()) - 1]) < LongNumber::eps and abs(y[i]) > LongNumber::eps)
                return std::make_tuple(VecND_LC(0), Mat2D_LC(0));
        VecND_LC x((int) std::get<2>(pluq).mat[0].vec.size());
        for (int i = index_first_not_null; i >= 0; --i) {
            LongComplex sum = LongComplex::czero;
            for (int j = index_first_not_null; j > i; --j) {
                move_with_double_round(sum, sum + x[j] * std::get<2>(pluq)[i][j]);
            }
            if (abs((y[i] - sum) / std::get<2>(pluq)[i][i]) > LongNumber::eps)
                move_with_double_round(x[i], (y[i] - sum) / std::get<2>(pluq)[i][i]);
        }
        for (int i = 0; i < std::get<2>(pluq).mat[0].vec.size() -
                            std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()); ++i) {
            for (int j = (int) std::get<2>(pluq).mat.size() - 1; j >= 0; --j) {
                LongComplex sum = LongComplex::czero;
                for (int k = (int) std::get<2>(pluq).mat[0].vec.size() - 1; k > j; --k) {
                    move_with_double_round(sum, sum + std::get<2>(pluq)[j][k] * c[k][i]);
                }
                //хуйня! зато какая ↓
                if (abs(std::get<2>(pluq)[j][j]) > LongNumber::eps) {
                    move_with_double_round(c[j][i], (-sum) / std::get<2>(pluq)[j][j]);
                    if (abs(c[j][i]) < LongNumber::eps)
                        c[j][i] = LongComplex::czero;
                } else {
                    if (abs(sum) < LongNumber::eps)
                        c[j][i] = LongComplex::czero;
                    else {
                        c[j][i] = LongComplex(1);
                        c[(int) std::get<2>(pluq).mat.size() + i][i] = LongComplex::czero;
                    }
                }
            }
        }
        if (index_first_not_null == std::max(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()) - 1)
            return std::make_tuple(VecND_LC(std::get<3>(pluq) * x), Mat2D_LC(0));
        else
            return std::make_tuple(VecND_LC(std::get<3>(pluq) * x), Mat2D_LC(std::get<3>(pluq) * c));
    }
    throw std::length_error("Incorrect solve: matrix does not match the size of the vector");
}

std::tuple<int, int, LongComplex> Mat2D_LC::max_elem(const Mat2D_LC &matrix, int index) const {
    int x = index, y = index;
    LongComplex max = matrix[index][index];
    for (int i = index; i < matrix.mat.size(); ++i) {
        for (int j = index; j < matrix.mat[0].vec.size(); ++j) {
            if (abs(matrix[i][j]) > abs(max)) {
                x = i;
                y = j;
                copy_with_double_round(max, matrix[i][j]);
            }
        }
    }
    return std::make_tuple(x, y, max);
}

std::tuple<Mat2D_LC, Mat2D_LC, Mat2D_LC, Mat2D_LC> Mat2D_LC::lu_decomposition() const {
    Mat2D_LC u(*this);
    Mat2D_LC p = c_eye((int) this->mat.size()), q = c_eye((int) this->mat[0].vec.size()), l((int) this->mat.size());
    for (int i = 0; i < std::min(this->mat.size(), this->mat[0].vec.size()); ++i) {
        auto maximum = max_elem(u, i);
        int index_row = std::get<0>(maximum), index_column = std::get<1>(maximum);
        LongComplex elem = std::get<2>(maximum);
        if (index_row != i) {
            std::swap(u[i], u[index_row]);
            std::swap(p[i], p[index_row]);
            std::swap(l[i], l[index_row]);
        }
        if (index_column != i) {
            for (int j = 0; j < this->mat.size(); ++j) {
                auto tmp = u[j][i];
                move_with_double_round(u[j][i], std::move(u[j][index_column]));
                move_with_double_round(u[j][index_column], std::move(tmp));
            }
            for (int j = 0; j < this->mat[0].vec.size(); ++j) {
                std::swap(q[j][i], q[j][index_column]);
            }
        }
        if (abs(elem) > LongNumber::eps) {
            for (int j = i + 1; j < this->mat.size(); ++j) {
                move_with_double_round(l[j][i], u[j][i] / u[i][i]);
                VecND_LC v1((int) this->mat[0].vec.size());
                for (int k = 0; k < this->mat[0].vec.size(); ++k)
                    move_with_double_round(v1[k], u[j][k] - u[i][k] * u[j][i] / u[i][i]);
                u[j] = v1;
            }
        }
    }
    for (int i = 0; i < this->mat.size(); ++i) {
        l[i][i] = LongComplex::one;
    }
    return std::make_tuple(Mat2D_LC(p), Mat2D_LC(l), Mat2D_LC(u), Mat2D_LC(q));
}

Mat2D_LC::Mat2D_LC(int x_) {
    mat.resize(x_);
    for (int i = 0; i < x_; ++i) {
        mat[i] = VecND_LC(x_);
    }
}

int Mat2D_LC::size() const {
    return (int) mat.size();
}

Mat2D_LC::Mat2D_LC(Mat2D_LC &&el) noexcept {
    mat = std::move(el.mat);
}

Mat2D_LC &Mat2D_LC::operator=(Mat2D_LC &&rhs) noexcept {
    if (this == &rhs)
        return *this;
    mat = std::move(rhs.mat);
    return *this;
}

Mat2D_LC &Mat2D_LC::operator=(VecND_LC &&rhs) noexcept {
    mat.resize(1);
    mat[0] = std::move(rhs);
    return *this;
}

LongNumber Mat2D_LC::rang() const {
    auto pluq = (*this).lu_decomposition();
    int min_size = std::min(std::get<2>(pluq).size(), std::get<2>(pluq)[0].size());
    LongNumber R(min_size);
    for (int i = min_size - 1; i >= 0; --i) {
        if (abs(std::get<2>(pluq)[i][i]) <= LongNumber::eps) {
            --R;
        } else {
            break;
        }
    }
    return R;
}

Mat2D_LC Mat2D_LC::inv() const {
    if (this->size() == this->operator[](0).size()) {
        auto pluq = (*this).lu_decomposition();
        if (abs(std::get<2>(pluq)[this->size() - 1][this->size() - 1]) <= LongNumber::eps) {
            throw std::logic_error("The determinant must not be equal to 0");
        }
        Mat2D_LC p = std::get<0>(pluq).T();
        Mat2D_LC y(this->size());
        for (int k = 0; k < this->size(); ++k) {
            for (int i = 0; i < this->size(); ++i) {
                LongComplex sum = LongComplex::czero;
                for (int j = 0; j < i; ++j) {
                    move_with_double_round(sum, sum + y[j][k] * std::get<1>(pluq)[i][j]);
                }
                move_with_double_round(y[i][k], p[k][i] - sum);
            }
        }
        Mat2D_LC x(this->size());
        for (int k = 0; k < this->size(); ++k) {
            for (int i = this->size() - 1; i >= 0; --i) {
                LongComplex sum = LongComplex::czero;
                for (int j = this->size() - 1; j > i; --j) {
                    move_with_double_round(sum, sum + x[j][k] * std::get<2>(pluq)[i][j]);
                }
                if (abs((y[i][k] - sum) / std::get<2>(pluq)[i][i]) > LongNumber::eps)
                    move_with_double_round(x[i][k], (y[i][k] - sum) / std::get<2>(pluq)[i][i]);
            }
        }
        return std::get<3>(pluq) * x;
    }
    throw std::logic_error("Incorrect inversion: the matrix is not square");
}

void print_solve(const std::tuple<VecND_LC, Mat2D_LC> &xc) {
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

