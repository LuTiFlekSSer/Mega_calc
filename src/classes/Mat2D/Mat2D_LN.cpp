#include "Mat2D_LN.h"
#include "cmath"


Mat2D_LN::Mat2D_LN(int x_, int y_) {
    mat.resize(x_);
    for (int i = 0; i < x_; ++i) {
        mat[i] = VecND_LN(y_);
    }
}

void Mat2D_LN::print() {
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

const VecND_LN &Mat2D_LN::operator[](int index) const {
    if (index < this->mat.size()) {
        return mat[index];
    }
    throw std::length_error("Matrix: invalid index");
}

VecND_LN &Mat2D_LN::operator[](int index) {
    if (index < this->mat.size()) {
        return mat[index];
    }
    throw std::length_error("Matrix: invalid index");
}

Mat2D_LN Mat2D_LN::operator+(const Mat2D_LN &rhs) {
    if (this->mat.size() == rhs.mat.size() and this->mat[0].vec.size() == rhs.mat[0].vec.size()) {
        Mat2D_LN tmp((int) mat.size(), (int) mat[0].vec.size());
        for (int i = 0; i < mat.size(); ++i) {
            for (int j = 0; j < mat[0].vec.size(); ++j) {
                tmp[i][j] = mat[i][j] + rhs.mat[i].vec[j];
            }
        }
        return Mat2D_LN{tmp};
    }
    throw std::length_error("Incorrect addition: different dimensions of matrix");
}

Mat2D_LN Mat2D_LN::operator-(const Mat2D_LN &rhs) {
    if (this->mat.size() == rhs.mat.size() and this->mat[0].vec.size() == rhs.mat[0].vec.size()) {
        Mat2D_LN tmp((int) mat.size(), (int) mat[0].vec.size());
        for (int i = 0; i < mat.size(); ++i) {
            for (int j = 0; j < mat[0].vec.size(); ++j) {
                tmp[i][j] = mat[i][j] - rhs.mat[i].vec[j];
            }
        }
        return Mat2D_LN{tmp};
    }
    throw std::length_error("Incorrect subtraction: different dimensions of matrix");
}

Mat2D_LN::Mat2D_LN(const Mat2D_LN &el) {
    mat.resize(el.mat.size());
    for (int i = 0; i < mat.size(); ++i) {
        mat[i] = el.mat[i];
    }
}

Mat2D_LN &Mat2D_LN::operator=(const Mat2D_LN &rhs) {
    mat.resize(rhs.mat.size());
    for (int i = 0; i < mat.size(); ++i) {
        mat[i] = rhs.mat[i];
    }
    return *this;
}

Mat2D_LN Mat2D_LN::operator*(const Mat2D_LN &rhs) {
    if (this->mat[0].vec.size() == rhs.mat.size()) {
        Mat2D_LN tmp((int) mat.size(), (int) rhs.mat[0].vec.size());
        for (int i = 0; i < mat.size(); ++i) {
            for (int j = 0; j < rhs.mat[0].vec.size(); ++j) {
                for (int k = 0; k < mat[0].vec.size(); ++k) {
                    tmp[i][j] += mat[i][k] * rhs.mat[k].vec[j];
                }
            }
        }
        return Mat2D_LN{tmp};
    }
    throw std::length_error("Incorrect multiplication: different matrix sizes");
}

Mat2D_LN Mat2D_LN::T() {
    Mat2D_LN tmp((int) this->mat[0].vec.size(), (int) this->mat.size());
    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat[0].vec.size(); ++j) {
            tmp[j][i] = this->mat[i][j];
        }
    }
    return Mat2D_LN{tmp};
}

LongNumber rec_det(const Mat2D_LN &m) {
    if (m.size() == 1) {
        return m[0][0];
    } else if (m.size() == 2) {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    } else {
        LongNumber result;
        for (int i = 0; i < m.size(); ++i) {
            Mat2D_LN minor(m.size() - 1, m.size() - 1);
            int x = 0, y = 0;
            for (int j = 1; j < m.size(); ++j) {
                for (int k = 0; k < m[0].size(); ++k) {
                    if (k == i)
                        continue;
                    minor[x][y++] = m[j][k];
                }
                y = 0;
                ++x;
            }
            result += rec_det(minor) * pow(-LongNumber::one, i) * m[0][i];
        }
        return result;
    }
}

LongNumber Mat2D_LN::det() {
    if (this->mat.size() == this->mat[0].vec.size()) {
        if (this->mat.size() < 8) {
            return rec_det(*this);
        }
        auto pluq = (*this).lu_decomposition();
        VecND_LN liner_p((int) std::get<0>(pluq).mat.size());
        for (int i = 0; i < std::get<0>(pluq).mat.size(); ++i) {
            for (int j = 0; j < std::get<0>(pluq).mat.size(); ++j) {
                if (std::get<0>(pluq)[i][j] == LongNumber::one) {
                    liner_p[i] = LongNumber(j);
                    break;
                }
            }
        }
        VecND_LN liner_q((int) std::get<3>(pluq).mat.size());
        for (int i = 0; i < std::get<3>(pluq).mat.size(); ++i) {
            for (int j = 0; j < std::get<3>(pluq).mat.size(); ++j) {
                if (std::get<3>(pluq)[i][j] == LongNumber::one) {
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
        LongNumber determ = LongNumber::one;
        for (int i = 0; i < std::get<2>(pluq).mat.size(); ++i) {
            determ *= std::get<2>(pluq)[i][i];
        }
        return determ * LongNumber(pow(-1, res));
    }
    throw std::length_error("Incorrect determinant: the matrix is not square");
}

VecND_LN Mat2D_LN::operator*(const VecND_LN &rhs) {
    if (this->mat[0].vec.size() == rhs.vec.size()) {
        Mat2D_LN tmp(1, (int) rhs.vec.size()), rhs_mat(1, (int) rhs.vec.size());
        rhs_mat[0] = rhs;
        tmp = *this * rhs_mat.T();
        return VecND_LN{tmp.T()[0]};
    }
    throw std::length_error("Incorrect multiplication: different matrix and vector sizes");
}

Mat2D_LN &Mat2D_LN::operator=(const VecND_LN &rhs) {
    mat.resize(1);
    mat[0] = rhs;
    return *this;
}

Mat2D_LN::Mat2D_LN() = default;

Mat2D_LN Mat2D_LN::operator*(const LongNumber &rhs) {
    Mat2D_LN tmp(*this);
    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat[0].vec.size(); ++j) {
            tmp[i][j] *= rhs;
        }
    }
    return Mat2D_LN{tmp};
}

Mat2D_LN eye(int size) {
    Mat2D_LN tmp(size, size);
    for (int i = 0; i < size; ++i) {
        tmp[i][i] = LongNumber::one;
    }
    return Mat2D_LN{tmp};
}

std::tuple<VecND_LN, Mat2D_LN> Mat2D_LN::solve(VecND_LN &b) {
    if (this->mat.size() == b.vec.size()) {
        auto pluq = (*this).lu_decomposition();
        VecND_LN pb = std::get<0>(pluq) * b;
        Mat2D_LN c((int) std::get<2>(pluq).mat[0].vec.size(), (int) std::get<2>(pluq).mat[0].vec.size() - (int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()));
        for (int i = (int) std::get<2>(pluq).mat[0].vec.size() - (int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()) - 1; i >= 0; --i) {
            c[i + (int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size())][i] = LongNumber::one;
        }
        VecND_LN y((int) std::get<2>(pluq).mat.size());
        Mat2D_LN yc((int) std::get<2>(pluq).mat.size(), (int) std::get<2>(pluq).mat[0].vec.size() - (int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()));
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
                    return std::make_tuple(VecND_LN(0), Mat2D_LN(0));
            } else {
                index_first_not_null = i;
                break;
            }
        }
        for (int i = (int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()) - 1; i < std::get<2>(pluq).mat.size(); ++i)
            if (abs(std::get<2>(pluq)[i][(int) std::min(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()) - 1]) < LongNumber::eps and abs(y[i]) > LongNumber::eps)
                return std::make_tuple(VecND_LN(0), Mat2D_LN(0));
        VecND_LN x((int) std::get<2>(pluq).mat[0].vec.size());
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
                        c[j][i] = LongNumber::one;
                        c[(int) std::get<2>(pluq).mat.size() + i][i] = LongNumber::zero;
                    }
                }
            }
        }
        if (index_first_not_null == std::max(std::get<2>(pluq).mat.size(), std::get<2>(pluq).mat[0].vec.size()) - 1)
            return std::make_tuple(VecND_LN(std::get<3>(pluq) * x), Mat2D_LN(0));
        else
            return std::make_tuple(VecND_LN(std::get<3>(pluq) * x), Mat2D_LN(std::get<3>(pluq) * c));
    }
    throw std::length_error("Incorrect solve: matrix does not match the size of the vector");
}

std::tuple<int, int, LongNumber> Mat2D_LN::max_elem(Mat2D_LN &matrix, int index) {
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

std::tuple<Mat2D_LN, Mat2D_LN, Mat2D_LN, Mat2D_LN> Mat2D_LN::lu_decomposition() {
    Mat2D_LN u(*this);
    Mat2D_LN p = eye((int) this->mat.size()), q = eye((int) this->mat[0].vec.size()), l((int) this->mat.size());
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
                VecND_LN v1((int) this->mat[0].vec.size());
                for (int k = 0; k < this->mat[0].vec.size(); ++k)
                    move_with_double_round(v1[k], u[j][k] - u[i][k] * u[j][i] / u[i][i]);
                u[j] = v1;
            }
        }
    }
    for (int i = 0; i < this->mat.size(); ++i) {
        l[i][i] = LongNumber::one;
    }
    for (int i = 0; i < u.size(); ++i) {
        for (int j = 0; j < u[0].size(); ++j) {
            u[i][j] = u[i][j];
            l[i][j] = l[i][j];
        }
    }
    return std::make_tuple(Mat2D_LN(p), Mat2D_LN(l), Mat2D_LN(u), Mat2D_LN(q));
}

Mat2D_LN::Mat2D_LN(int x_) {
    mat.resize(x_);
    for (int i = 0; i < x_; ++i) {
        mat[i] = VecND_LN(x_);
    }
}

int Mat2D_LN::size() const {
    return (int) mat.size();
}

Mat2D_LN::Mat2D_LN(Mat2D_LN &&el) noexcept {
    mat = std::move(el.mat);
}

Mat2D_LN &Mat2D_LN::operator=(Mat2D_LN &&rhs) noexcept {
    if (this == &rhs)
        return *this;
    mat = std::move(rhs.mat);
    return *this;
}

Mat2D_LN &Mat2D_LN::operator=(VecND_LN &&rhs) noexcept {
    mat.resize(1);
    mat[0] = std::move(rhs);
    return *this;
}

void print_solve(std::tuple<VecND_LN, Mat2D_LN> xc) {
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

