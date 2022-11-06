#include <iostream>
#include "src/classes/Mat2D/Mat2D.h"
#include "algorithm"

int main() {
    Mat2D m(5,3), A, B;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cin >> m[i][j];
        }
    }
    auto i = m.lu_decomposition();
    A = std::get<1>(i) * std::get<2>(i);
    B = std::get<0>(i) * m * std::get<3>(i);
    A.print();
    B.print();
    return 0;
}
