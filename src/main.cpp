#include <iostream>
#include "src/classes/Mat2D/Mat2D.h"
#include "src/classes/VecND/VecND.h"
#include "src/classes/LongNumber/LongNumber.h"
#include "src/classes/LongComplex/LongComplex.h"
#include "ui files/ui.h"
#include "sstream"

#include <vector>

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
    LongComplex a;
    std::cin >> a;
    std::cout << a;
    return 0;
}

