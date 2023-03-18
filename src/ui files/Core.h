#ifndef MEGA_CALCAPP_CORE_H
#define MEGA_CALCAPP_CORE_H


#include "iostream"
#include "QObject"
#include "QString"
#include "unistd.h"
#include "QInternal"

class Core : public QObject {
Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr) : QObject(parent) {}

signals:

    void send_ans(QString ans);

public slots:

    void solve_expr(const QString &expr);

};

#endif //MEGA_CALCAPP_CORE_H
