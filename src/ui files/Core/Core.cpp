#include "Core.h"
#include "thread"
#include "../../classes/Parser/Parser.h"
#include "../../classes/Solver/Solver.h"
#include "../../classes/Mat2D/Mat2D.h"

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

void Core::mult(const QList<QList<QString>> &m1, const QList<QList<QString>> &m2) {
    try {
        Mat2D a((int) m1.size(), (int) m1[0].size()), b((int) m2.size(), (int) m2[0].size());
        for (int i = 0; i < a.size(); ++i) {
            for (int j = 0; j < a[0].size(); ++j) {
                a[i][j] = LongNumber(m1[i][j].toStdString());
            }
        }
        for (int i = 0; i < b.size(); ++i) {
            for (int j = 0; j < b[0].size(); ++j) {
                b[i][j] = LongNumber(m2[i][j].toStdString());
            }
        }
        Mat2D c = a * b;
        QList<QList<QString>> result(c.size());
        for (int i = 0; i < c.size(); ++i) {
            result[i].resize(c[0].size());
            for (int j = 0; j < c[0].size(); ++j) {
                result[i][j] = QString::fromStdString(c[i][j].to_string());
            }
        }
        emit send_matrix(result, c.size(), c[0].size(), 2);
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
    emit(send_matrix(result, result.size(), result[0].size(), index));
}

void Core::transpose_matrix(const QList<QList<QString>> &m1, int index) {
    std::thread t([m1, index, this] { transpose(m1, index); });
    t.detach();
}



