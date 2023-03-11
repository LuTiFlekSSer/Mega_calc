#include <iostream>
#include "src/classes/LongNumber/LongNumber.h"
#include "src/classes/LongComplex/LongComplex.h"
#include "src/classes/Mat2D/Mat2D.h"
#include "src/classes/VecND/VecND.h"
#include "ui files/ui.h"
#include "chrono"

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
//   start_UI(argc, argv);
    LongComplex a, b;
    std::cin >> a;
    std::cout << a << '\n';
//    auto t1 = std::chrono::steady_clock::now();
//    for (int i = 0; i < 1000; ++i) {
//        sqrt(a);
//    }
//    std::cout << std::chrono::duration<double>(std::chrono::steady_clock::now() - t1).count() << '\n';
    std::cout << ln(a);
    return 0;
}
