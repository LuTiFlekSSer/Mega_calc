//
// Created by boris on 15.03.2023.
//

#include "Core.h"
#include "unistd.h"
#include "thread"

void Core::solve(const QString &expr) {
    sleep(1);
    std::cout << expr.toStdString() << '\n';
    emit send_ans(QString("хихихиха"));
}

void Core::solve_expr(const QString &expr) {
    std::thread t([expr, this] { solve(expr); });
    t.detach();
}
