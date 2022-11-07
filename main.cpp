#include <iostream>
#include "src/classes/Mat2D/Mat2D.h"

int main() {
    Mat2D m(3, 3), A, B;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cin >> m[i][j];
        }
    }
    VecND v(3);
    for (int i = 0; i < 3; ++i) {
        std::cin >> v[i];
    }
    auto i = m.solve(v);
    std::get<0>(i).print();
    std::get<1>(i).print();
    return 0;
}
