#include <iostream>

#include "Vector/lib/Vector.cpp"
#include "Matrix/lib/Matrix.cpp"

using std::cout;
using std::endl;

int main() {

    float simpleData[4] = {1.0f, 2.0f, 3.0f, 4.0f};

    AMathEngine::Matrix<float> M(2, 2, simpleData);
    M.print();

    return 0;
}