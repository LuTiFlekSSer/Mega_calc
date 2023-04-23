#ifndef MEGA_CALCAPP_CORE_H
#define MEGA_CALCAPP_CORE_H


#include "iostream"
#include "QObject"
#include "QString"
#include "QList"

class Core : public QObject {
Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr) : QObject(parent) {}

    void solve(const QString &expr);

    void mult(const QList<QList<QString>> &m1, const QList<QList<QString>> &m2);

    void swap(const QList<QList<QString>> &m1, const QList<QList<QString>> &m2);

    void transpose(const QList<QList<QString>> &m1, int index);

signals:

    void send_error(QString err);

    void send_ans(QString ans);

    void send_matrix(QList<QList<QString>> m, int x, int y, int index);

public slots:

    void mult_matrix(const QList<QList<QString>> &m1, const QList<QList<QString>> &m2);

    void swap_matrix(const QList<QList<QString>> &m1, const QList<QList<QString>> &m2);

    void transpose_matrix(const QList<QList<QString>> &m1, int index);
//    void sum_matrix(const QList<QList<QString>> &m1, const QList<QList<QString>> &m2);
//
//    void dif_matrix(const QList<QList<QString>> &m1, const QList<QList<QString>> &m2);
//
//    void solve_matrix(const QList<QList<QString>> &m1, const QList<QList<QString>> &m2);
//
//    void mult_matrix_on_num(const QList<QList<QString>> &m1, int num, int index);
//
//    void pow_matrix_in_num(const QList<QList<QString>> &m1, int num, int index);

    void solve_expr(const QString &expr);

};

#endif //MEGA_CALCAPP_CORE_H
