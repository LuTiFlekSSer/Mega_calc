#include "Core.h"
#include "thread"
#include "../../classes/Parser/Parser.h"
#include "../../classes/Solver/Solver.h"
#include "src/classes/Mat2D/Mat2D_LN.h"
#include "src/classes/Mat2D/Mat2D_LC.h"

void Core::solve(const QString &expr) {
    try {
        auto p = parser(expr.toStdString());
        auto s = solver(p);
        emit send_ans(QString::fromStdString(s));
    } catch (std::exception &e) {
        emit send_error(QString(e.what()));
    }
}

void Core::solve_expr(const QString &expr) {
    std::thread t([expr, this] { solve(expr); });
    t.detach();
}

std::tuple<std::vector<std::vector<std::string>>, bool> calculate_matrix(const QList<QList<QString>> &m1) {
    std::vector<std::vector<std::string>> m1_str(m1.size());
    bool m1_real = true;
    for (int i = 0; i < m1.size(); ++i) {
        m1_str[i].resize(m1[0].size());
        for (int j = 0; j < m1[0].size(); ++j) {
            auto p = parser(m1[i][j].toStdString());
            m1_str[i][j] = solver(p);
            if (!correct_long_num(m1_str[i][j])) {
                m1_real = false;
            }
        }
    }
    return std::make_tuple(m1_str, m1_real);
}

void Core::mult(const QList<QList<QString>> &m1, const QList<QList<QString>> &m2) {
    try {
        auto m1_parse = calculate_matrix(m1), m2_parse = calculate_matrix(m2);
        auto m1_str = std::get<0>(m1_parse), m2_str = std::get<0>(m2_parse);
        auto m1_real = std::get<1>(m1_parse), m2_real = std::get<1>(m2_parse);

        if (m1_real and m2_real) {
            Mat2D_LN a((int) m1_str.size(), (int) m1[0].size()), b((int) m2_str.size(), (int) m2[0].size());
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[0].size(); ++j) {
                    move_with_double_round(a[i][j], LongNumber(m1_str[i][j]));
                }
            }

            for (int i = 0; i < b.size(); ++i) {
                for (int j = 0; j < b[0].size(); ++j) {
                    move_with_double_round(b[i][j], LongNumber(m2_str[i][j]));
                }
            }

            auto c = a * b;
            QList<QList<QString>> result(c.size());
            for (int i = 0; i < c.size(); ++i) {
                result[i].resize(c[0].size());
                for (int j = 0; j < c[0].size(); ++j) {
                    LongNumber tmp;
                    tmp = c[i][j];
                    result[i][j] = QString::fromStdString(tmp.to_string());
                }
            }
            emit send_matrix(result, c.size(), c[0].size(), 2);
        } else {
            Mat2D_LC a((int) m1_str.size(), (int) m1[0].size()), b((int) m2_str.size(), (int) m2[0].size());
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[0].size(); ++j) {
                    move_with_double_round(a[i][j], LongComplex(m1_str[i][j]));
                }
            }

            for (int i = 0; i < b.size(); ++i) {
                for (int j = 0; j < b[0].size(); ++j) {
                    move_with_double_round(b[i][j], LongComplex(m2_str[i][j]));
                }
            }

            auto c = a * b;
            QList<QList<QString>> result(c.size());
            for (int i = 0; i < c.size(); ++i) {
                result[i].resize(c[0].size());
                for (int j = 0; j < c[0].size(); ++j) {
                    LongComplex tmp;
                    tmp = c[i][j];
                    result[i][j] = QString::fromStdString(tmp.to_string());
                }
            }
            emit send_matrix(result, c.size(), c[0].size(), 2);
        }
    } catch (std::exception &e) {
        emit send_error(QString(e.what()));
    }
}

void Core::mult_matrix(const QList<QList<QString>> &m1, const QList<QList<QString>> &m2) {
    std::thread t([m1, m2, this] { mult(m1, m2); });
    t.detach();
}

void Core::swap(const QList<QList<QString>> &m1, const QList<QList<QString>> &m2) {
    emit(send_matrix(m2, (int) m2.size(), (int) m2[0].size(), 0));
    emit(send_matrix(m1, (int) m1.size(), (int) m1[0].size(), 1));
}

void Core::swap_matrix(const QList<QList<QString>> &m1, const QList<QList<QString>> &m2) {
    std::thread t([m1, m2, this] { swap(m1, m2); });
    t.detach();
}

void Core::transpose(const QList<QList<QString>> &m1, int index) {
    QList<QList<QString>> result(m1[0].size());
    for (int i = 0; i < m1[0].size(); ++i) {
        result[i].resize(m1.size());
        for (int j = 0; j < m1.size(); ++j) {
            result[i][j] = m1[j][i];
        }
    }
    emit(send_matrix(result, (int) result.size(), (int) result[0].size(), index));
}

void Core::transpose_matrix(const QList<QList<QString>> &m1, int index) {
    std::thread t([m1, index, this] { transpose(m1, index); });
    t.detach();
}

void Core::sum(const QList<QList<QString>> &m1, const QList<QList<QString>> &m2) {
    try {
        auto m1_parse = calculate_matrix(m1), m2_parse = calculate_matrix(m2);
        auto m1_str = std::get<0>(m1_parse), m2_str = std::get<0>(m2_parse);
        auto m1_real = std::get<1>(m1_parse), m2_real = std::get<1>(m2_parse);

        if (m1_real and m2_real) {
            Mat2D_LN a((int) m1_str.size(), (int) m1[0].size()), b((int) m2_str.size(), (int) m2[0].size());
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[0].size(); ++j) {
                    move_with_double_round(a[i][j], LongNumber(m1_str[i][j]));
                }
            }

            for (int i = 0; i < b.size(); ++i) {
                for (int j = 0; j < b[0].size(); ++j) {
                    move_with_double_round(b[i][j], LongNumber(m2_str[i][j]));
                }
            }

            auto c = a + b;
            QList<QList<QString>> result(c.size());
            for (int i = 0; i < c.size(); ++i) {
                result[i].resize(c[0].size());
                for (int j = 0; j < c[0].size(); ++j) {
                    LongNumber tmp;
                    tmp = c[i][j];
                    result[i][j] = QString::fromStdString(tmp.to_string());
                }
            }
            emit send_matrix(result, c.size(), c[0].size(), 2);
        } else {
            Mat2D_LC a((int) m1_str.size(), (int) m1[0].size()), b((int) m2_str.size(), (int) m2[0].size());
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[0].size(); ++j) {
                    move_with_double_round(a[i][j], LongComplex(m1_str[i][j]));
                }
            }

            for (int i = 0; i < b.size(); ++i) {
                for (int j = 0; j < b[0].size(); ++j) {
                    move_with_double_round(b[i][j], LongComplex(m2_str[i][j]));
                }
            }

            auto c = a + b;
            QList<QList<QString>> result(c.size());
            for (int i = 0; i < c.size(); ++i) {
                result[i].resize(c[0].size());
                for (int j = 0; j < c[0].size(); ++j) {
                    LongComplex tmp;
                    tmp = c[i][j];
                    result[i][j] = QString::fromStdString(tmp.to_string());
                }
            }
            emit send_matrix(result, c.size(), c[0].size(), 2);
        }
    } catch (std::exception &e) {
        emit send_error(QString(e.what()));
    }
}

void Core::sum_matrix(const QList<QList<QString>> &m1, const QList<QList<QString>> &m2) {
    std::thread t([m1, m2, this] { sum(m1, m2); });
    t.detach();
}


void Core::dif(const QList<QList<QString>> &m1, const QList<QList<QString>> &m2) {
    try {
        auto m1_parse = calculate_matrix(m1), m2_parse = calculate_matrix(m2);
        auto m1_str = std::get<0>(m1_parse), m2_str = std::get<0>(m2_parse);
        auto m1_real = std::get<1>(m1_parse), m2_real = std::get<1>(m2_parse);

        if (m1_real and m2_real) {
            Mat2D_LN a((int) m1_str.size(), (int) m1[0].size()), b((int) m2_str.size(), (int) m2[0].size());
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[0].size(); ++j) {
                    move_with_double_round(a[i][j], LongNumber(m1_str[i][j]));
                }
            }

            for (int i = 0; i < b.size(); ++i) {
                for (int j = 0; j < b[0].size(); ++j) {
                    move_with_double_round(b[i][j], LongNumber(m2_str[i][j]));
                }
            }

            auto c = a - b;
            QList<QList<QString>> result(c.size());
            for (int i = 0; i < c.size(); ++i) {
                result[i].resize(c[0].size());
                for (int j = 0; j < c[0].size(); ++j) {
                    LongNumber tmp;
                    tmp = c[i][j];
                    result[i][j] = QString::fromStdString(tmp.to_string());
                }
            }
            emit send_matrix(result, c.size(), c[0].size(), 2);
        } else {
            Mat2D_LC a((int) m1_str.size(), (int) m1[0].size()), b((int) m2_str.size(), (int) m2[0].size());
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[0].size(); ++j) {
                    move_with_double_round(a[i][j], LongComplex(m1_str[i][j]));
                }
            }

            for (int i = 0; i < b.size(); ++i) {
                for (int j = 0; j < b[0].size(); ++j) {
                    move_with_double_round(b[i][j], LongComplex(m2_str[i][j]));
                }
            }

            auto c = a - b;
            QList<QList<QString>> result(c.size());
            for (int i = 0; i < c.size(); ++i) {
                result[i].resize(c[0].size());
                for (int j = 0; j < c[0].size(); ++j) {
                    LongComplex tmp;
                    tmp = c[i][j];
                    result[i][j] = QString::fromStdString(tmp.to_string());
                }
            }
            emit send_matrix(result, c.size(), c[0].size(), 2);
        }
    } catch (std::exception &e) {
        emit send_error(QString(e.what()));
    }
}

void Core::dif_matrix(const QList<QList<QString>> &m1, const QList<QList<QString>> &m2) {
    std::thread t([m1, m2, this] { dif(m1, m2); });
    t.detach();
}

void Core::mult_on_num(const QList<QList<QString>> &m1, const QString &num, int index) {
    try {
        auto m1_parse = calculate_matrix(m1);
        auto m1_str = std::get<0>(m1_parse);
        auto m1_real = std::get<1>(m1_parse);
        auto p = parser(num.toStdString());
        auto s = solver(p);

        if (m1_real and correct_long_num(s)) {
            Mat2D_LN a((int) m1_str.size(), (int) m1[0].size());
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[0].size(); ++j) {
                    move_with_double_round(a[i][j], LongNumber(m1_str[i][j]));
                }
            }

            auto c = a * LongNumber(s);
            QList<QList<QString>> result(c.size());
            for (int i = 0; i < c.size(); ++i) {
                result[i].resize(c[0].size());
                for (int j = 0; j < c[0].size(); ++j) {
                    LongNumber tmp;
                    tmp = c[i][j];
                    result[i][j] = QString::fromStdString(tmp.to_string());
                }
            }
            emit send_matrix(result, c.size(), c[0].size(), index);
        } else {
            Mat2D_LC a((int) m1_str.size(), (int) m1[0].size());
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[0].size(); ++j) {
                    move_with_double_round(a[i][j], LongComplex(m1_str[i][j]));
                }
            }

            auto c = a * LongComplex(s);
            QList<QList<QString>> result(c.size());
            for (int i = 0; i < c.size(); ++i) {
                result[i].resize(c[0].size());
                for (int j = 0; j < c[0].size(); ++j) {
                    LongComplex tmp;
                    tmp = c[i][j];
                    result[i][j] = QString::fromStdString(tmp.to_string());
                }
            }
            emit send_matrix(result, c.size(), c[0].size(), index);
        }
    } catch (std::exception &e) {
        emit send_error(QString(e.what()));
    }
}

void Core::mult_matrix_on_num(const QList<QList<QString>> &m1, const QString &num, int index) {
    std::thread t([m1, num, index, this] { mult_on_num(m1, num, index); });
    t.detach();
}

void Core::pow_in_num(const QList<QList<QString>> &m1, const QString &num, int index) {
    try {
        auto m1_parse = calculate_matrix(m1);
        auto m1_str = std::get<0>(m1_parse);
        auto m1_real = std::get<1>(m1_parse);
        auto p = parser(num.toStdString());
        auto s = solver(p);

        if (!correct_long_num(s) or LongNumber(s) <= LongNumber::zero) {
            throw std::logic_error("The degree must be a natural number");
        }

        if (m1_real) {
            Mat2D_LN a((int) m1_str.size(), (int) m1[0].size());
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[0].size(); ++j) {
                    move_with_double_round(a[i][j], LongNumber(m1_str[i][j]));
                }
            }
            auto deg = LongNumber(s);
            auto c = a;
            for (auto i = LongNumber::one; i < deg; ++i) {
                c = c * a;
            }

            QList<QList<QString>> result(c.size());
            for (int i = 0; i < c.size(); ++i) {
                result[i].resize(c[0].size());
                for (int j = 0; j < c[0].size(); ++j) {
                    LongNumber tmp;
                    tmp = c[i][j];
                    result[i][j] = QString::fromStdString(tmp.to_string());
                }
            }
            emit send_matrix(result, c.size(), c[0].size(), index);
        } else {
            Mat2D_LC a((int) m1_str.size(), (int) m1[0].size());
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[0].size(); ++j) {
                    move_with_double_round(a[i][j], LongComplex(m1_str[i][j]));
                }
            }

            auto deg = LongNumber(s);
            auto c = a;
            for (auto i = LongNumber::one; i < deg; ++i) {
                c = c * a;
            }

            QList<QList<QString>> result(c.size());
            for (int i = 0; i < c.size(); ++i) {
                result[i].resize(c[0].size());
                for (int j = 0; j < c[0].size(); ++j) {
                    LongComplex tmp;
                    tmp = c[i][j];
                    result[i][j] = QString::fromStdString(tmp.to_string());
                }
            }
            emit send_matrix(result, c.size(), c[0].size(), index);
        }
    } catch (std::exception &e) {
        emit send_error(QString(e.what()));
    }
}

void Core::pow_matrix_in_num(const QList<QList<QString>> &m1, const QString &num, int index) {
    std::thread t([m1, num, index, this] { pow_in_num(m1, num, index); });
    t.detach();
}

void Core::det(const QList<QList<QString>> &m1) {
    try {
        auto m1_parse = calculate_matrix(m1);
        auto m1_str = std::get<0>(m1_parse);
        auto m1_real = std::get<1>(m1_parse);

        if (m1_real) {
            Mat2D_LN a((int) m1_str.size(), (int) m1[0].size());
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[0].size(); ++j) {
                    move_with_double_round(a[i][j], LongNumber(m1_str[i][j]));
                }
            }

            Mat2D_LN c(1, 1);
            c[0][0] = a.det();
            QList<QList<QString>> result(c.size());
            for (int i = 0; i < c.size(); ++i) {
                result[i].resize(c[0].size());
                for (int j = 0; j < c[0].size(); ++j) {
                    result[i][j] = QString::fromStdString(c[i][j].to_string());
                }
            }
            emit send_matrix(result, c.size(), c[0].size(), 2);
        } else {
            Mat2D_LC a((int) m1_str.size(), (int) m1[0].size());
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[0].size(); ++j) {
                    move_with_double_round(a[i][j], LongComplex(m1_str[i][j]));
                }
            }

            Mat2D_LC c(1, 1);
            c[0][0] = a.det();
            QList<QList<QString>> result(c.size());
            for (int i = 0; i < c.size(); ++i) {
                result[i].resize(c[0].size());
                for (int j = 0; j < c[0].size(); ++j) {
                    result[i][j] = QString::fromStdString(c[i][j].to_string());
                }
            }
            emit send_matrix(result, c.size(), c[0].size(), 2);
        }
    } catch (std::exception &e) {
        emit send_error(QString(e.what()));
    }
}

void Core::determinant(const QList<QList<QString>> &m1) {
    std::thread t([m1, this] { det(m1); });
    t.detach();
}

void Core::rang(const QList<QList<QString>> &m1) {
    try {
        auto m1_parse = calculate_matrix(m1);
        auto m1_str = std::get<0>(m1_parse);
        auto m1_real = std::get<1>(m1_parse);

        if (m1_real) {
            Mat2D_LN a((int) m1_str.size(), (int) m1[0].size());
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[0].size(); ++j) {
                    move_with_double_round(a[i][j], LongNumber(m1_str[i][j]));
                }
            }

            Mat2D_LN c(1, 1);
            c[0][0] = a.rang();
            QList<QList<QString>> result(c.size());
            for (int i = 0; i < c.size(); ++i) {
                result[i].resize(c[0].size());
                for (int j = 0; j < c[0].size(); ++j) {
                    result[i][j] = QString::fromStdString(c[i][j].to_string());
                }
            }
            emit send_matrix(result, c.size(), c[0].size(), 2);
        } else {
            Mat2D_LC a((int) m1_str.size(), (int) m1[0].size());
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[0].size(); ++j) {
                    move_with_double_round(a[i][j], LongComplex(m1_str[i][j]));
                }
            }

            Mat2D_LN c(1, 1);
            c[0][0] = a.rang();
            QList<QList<QString>> result(c.size());
            for (int i = 0; i < c.size(); ++i) {
                result[i].resize(c[0].size());
                for (int j = 0; j < c[0].size(); ++j) {
                    result[i][j] = QString::fromStdString(c[i][j].to_string());
                }
            }
            emit send_matrix(result, c.size(), c[0].size(), 2);
        }
    } catch (std::exception &e) {
        emit send_error(QString(e.what()));
    }
}

void Core::matrix_rang(const QList<QList<QString>> &m1) {
    std::thread t([m1, this] { rang(m1); });
    t.detach();
}

void Core::inv(const QList<QList<QString>> &m1) {
    try {
        auto m1_parse = calculate_matrix(m1);
        auto m1_str = std::get<0>(m1_parse);
        auto m1_real = std::get<1>(m1_parse);

        if (m1_real) {
            Mat2D_LN a((int) m1_str.size(), (int) m1[0].size());
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[0].size(); ++j) {
                    move_with_double_round(a[i][j], LongNumber(m1_str[i][j]));
                }
            }

            Mat2D_LN c(a.size());
            c = a.inv();
            QList<QList<QString>> result(c.size());
            for (int i = 0; i < c.size(); ++i) {
                result[i].resize(c[0].size());
                for (int j = 0; j < c[0].size(); ++j) {
                    LongNumber tmp;
                    tmp = c[i][j];
                    result[i][j] = QString::fromStdString(tmp.to_string());
                }
            }
            emit send_matrix(result, c.size(), c[0].size(), 2);
        } else {
            Mat2D_LC a((int) m1_str.size(), (int) m1[0].size());
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[0].size(); ++j) {
                    move_with_double_round(a[i][j], LongComplex(m1_str[i][j]));
                }
            }

            Mat2D_LC c(a.size());
            c = a.inv();
            QList<QList<QString>> result(c.size());
            for (int i = 0; i < c.size(); ++i) {
                result[i].resize(c[0].size());
                for (int j = 0; j < c[0].size(); ++j) {
                    LongComplex tmp;
                    tmp = c[i][j];
                    result[i][j] = QString::fromStdString(tmp.to_string());
                }
            }
            emit send_matrix(result, c.size(), c[0].size(), 2);
        }
    } catch (std::exception &e) {
        emit send_error(QString(e.what()));
    }
}

void Core::matrix_inv(const QList<QList<QString>> &m1) {
    std::thread t([m1, this] { inv(m1); });
    t.detach();
}




