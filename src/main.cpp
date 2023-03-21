#include <iostream>
#include "src/classes/LongNumber/LongNumber.h"
#include "src/classes/LongComplex/LongComplex.h"
#include "src/classes/Mat2D/Mat2D.h"
#include "src/classes/VecND/VecND.h"
#include "src/ui files/Ui/ui.h"
#include "chrono"
#include "src/classes/Parser/Parser.h"

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
//    LongComplex a, b, c;
//    std::cin >> a >> b;
//    std::cout << a << ' ' << b << '\n';
//    auto t1 = std::chrono::steady_clock::now();
//    for (int i = 0; i < 1000; ++i) {
//        b = factorial(a);
//    }
//    std::cout << std::chrono::duration<double>(std::chrono::steady_clock::now() - t1).count() << '\n';
//    std::cout << factorial(a);
    Parser a("),(2)");
    return 0;
}
