#include <iostream>

#include "Vector/include/Vector.h"
#include "Vector/include/Vector3D.h"
#include "Matrix/include/Matrix.h"

using std::cout;
using std::endl;

int main() {
  
    vector<float> tempA{1.0f, 2.0f, 3.0f, 1.0f, 2.0f};
    vector<float> tempB{4.0f, 1.0f, 4.0f, 1.0f, 3.0f};
    vector<float> tempC{2.0f, -1.0f, 5.0f, 1.0f, 5.0f};
    vector<float> tempD{1.0f, 5.0f, 3.0f, 2.0f, 6.0f};

    AMathEngine::Vector a(tempA);
    AMathEngine::Vector b(tempB);
    AMathEngine::Vector c(tempC);
    AMathEngine::Vector d{tempD};

    // AMathEngine::Vector3D v1{3.0f, 1.0f, -1.0f};
    // AMathEngine::Vector3D v2{2.0f, 0.0f, 4.0f};
    // AMathEngine::Vector3D v3{-1.0f, -2.0f, 3.0f};

    // float mag = AMathEngine::magnitude(a);
    // float dot = AMathEngine::dot(a, a);
    // float angle = AMathEngine::find_angle(a, b);
    // float scalarTripleProduct = AMathEngine::scalar_triple_product(v1, v2, v3);

    vector<AMathEngine::Vector> m1 {a, b, c, d, d};

    AMathEngine::Matrix A(m1);

    return 0;
}