#include <iostream>
#include "src/classes/Mat2D/Mat2D.h"
#include "src/classes/VecND/VecND.h"
#include "src/classes/LongNumber/LongNumber.h"
#include "ui files/ui.h"
#include "cmath"

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
    LongNumber a("0.100022000047238465727623748562347856374621879546747815479162478526783451273645712345644217033"), b("-156435876236478568765487913256237895483.000222922220933");
//    std::cout << a * b;
    for (int i = 0; i < 1000000; ++i) {
        a + b;
    }

//    std::cout << a - b << ' ' << a + b << ' ' << (a - b == -(b - a)) << (a + b == b + a);
    return 0;
}

