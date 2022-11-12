#include <iostream>
#include "src/classes/Mat2D/Mat2D.h"

int main() {
    Mat2D m(3, 5);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            std::cin >> m[i][j];
        }
    }
    VecND v(3);
    for (int i = 0; i < 3; ++i) {
        std::cin >> v[i];
    }
    auto i = m.solve(v);
    VecND a = std::get<0>(i);
    for (int j = 0; j < std::get<1>(i).size(); ++j) {
        for (int k = 0; k < std::get<1>(i)[0].size(); ++k) {
            a[j] += std::get<1>(i)[j][k];
        }
    }
    std::cout << '\n';
    print_solve(i);
    v.print();
    (m * a).print();
    return 0;
}
