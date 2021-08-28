#include <iostream>

#include "Matrix3D.hpp"
#include "Vector3D.hpp"

int main() {
    Vector3D v1(1, 2, 3);
    Vector3D v2(1, 3, 4);
    Vector3D v3(2, 7, -5);
    Matrix3D M1(v1, v1, v1);
    Matrix3D M2(1, 2, 3, 0, 1, 4, 5, 6, 0);

    std::cout << "Det(M) = " << Determinant(M2) << std::endl;
    std::cout << "M^-1 = \n" << Inverse(M2) << std::endl;
    std::cout << "Det(M^-1) = " << Determinant(Inverse(M2)) << std::endl;

    return 0;
}