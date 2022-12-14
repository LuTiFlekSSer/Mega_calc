#include <iostream>
#include "src/classes/Mat2D/Mat2D.h"
#include "src/classes/VecND/VecND.h"
#include "src/classes/LongNumber/LongNumber.h"
#include "ui files/ui.h"

int main(int argc, char *argv[]) {
//    Mat2D m(3, 5);
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0; j < 5; ++j) {
//            std::cin >> m[i][j];
//        }
//    }
//    VecND v(3);
//    for (int i = 0; i < 3; ++i) {
//        std::cin >> v[i];
//    }
//    auto i = m.solve(v);
//    VecND a = std::get<0>(i);
//    for (int j = 0; j < std::get<1>(i).size(); ++j) {
//        for (int k = 0; k < std::get<1>(i)[0].size(); ++k) {
//            a[j] += std::get<1>(i)[j][k];
//        }
//    }
//    std::cout << '\n';
//    print_solve(i);
//    v.print();
//    (m * a).print();
//    start_UI(argc, argv);
    LongNumber a("111.111"), b("1"), c(-0.1), d, e;
    e = LongNumber::nan;
    d = LongNumber::inf;
    std::cout << max(a, b) << '\n';
    std::cout << a + b << '\n' << b + a << '\n' << LongNumber::inf << ' ' << LongNumber::nan << ' ' << LongNumber::infm << '\n';
    std::cout << isnan(LongNumber::nan) << ' ' << isnan(LongNumber::zero) << ' ' << isinf(LongNumber::nan) << ' ' << isinf(LongNumber::inf) << ' ' << isinf(LongNumber::infm);
    return 0;
}

