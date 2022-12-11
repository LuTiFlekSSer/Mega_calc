#include <iostream>
#include "src/classes/Mat2D/Mat2D.h"
#include "src/classes/VecND/VecND.h"
#include "src/classes/LongNumber/LongNimber.h"
#include "ui files/ui.h"

int main(int argc, char *argv[]) {
//    Mat2D m(4, 7);
//    for (int i = 0; i < 4; ++i) {
//        for (int j = 0; j < 7; ++j) {
//            std::cin >> m[i][j];
//        }
//    }
//    VecND v(4);
//    for (int i = 0; i < 4; ++i) {
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

//    std::cout << correct_num("+");
    LongNumber q("-123123");
    std::cout << q.to_string();
    return 0;
}

