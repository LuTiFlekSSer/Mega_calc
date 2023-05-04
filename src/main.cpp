#include "src/ui files/Ui/ui.h"
#include "src/classes/Solver/Solver.h"
#include "iostream"

int main(int argc, char *argv[]) {
    std::string s;
    std::cin >> s;
    auto p = parser(s);
    derivative_solver(p);
//    return start_UI(argc, argv);
}
