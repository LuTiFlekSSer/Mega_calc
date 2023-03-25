#include "Core.h"
#include "unistd.h"
#include "thread"
#include "../../classes/Parser/Parser.h"
#include "../../classes/Solver/Solver.h"

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
