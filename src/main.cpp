#include <iostream>
#include "src/classes/Mat2D/Mat2D.h"
#include "src/classes/VecND/VecND.h"
#include "src/classes/LongNumber/LongNumber.h"
#include "ui files/ui.h"

int main(int argc, char *argv[]) { // not NaN in == and !=
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
//    std::cout << -LongNumber::zero + LongNumber::zero;
//    for (int i = 0; i < 1000; ++i) {
//        sqrt(LongNumber("13521321354156413468543843685"));
//    }
//    std::cout << sqrt(LongNumber("0.0000000000000000000000000000000000001352132135415641346854384368513521321354156413468543843685")) << '\n';
//    for (int i = 0; i < 1000; ++i) {
//        surd(LongNumber(123), LongNumber("2"));
//    }
//    std::cout << surd(LongNumber("0.0000000000000000000000000000000000001352132135415641346854384368513521321354156413468543843685"), LongNumber(2)) << '\n';
    std::cout << surd(LongNumber("8"), LongNumber("inf"));
//   start_UI(argc, argv);
    return 0;
}

