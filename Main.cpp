#include <iostream>

#include "Matrix3D.hpp"
#include "Vector3D.hpp"

int main() {
    // Testing
    Vector3D v1(1, 2, 3);
    Matrix3D M1(v1, v1, v1);
    Matrix3D M2(1, 2, 3, 4, 5, 6, 7, 8, 9);

    std::cout << M1 << std::endl;
    std::cout << M2 << std::endl;

    return 0;
}