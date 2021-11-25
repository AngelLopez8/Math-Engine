#include <iostream>

#include "Vector/lib/Vector.cpp"
#include "Matrix/lib/Matrix.cpp"

using std::cout;
using std::endl;

int main() {

    float simpleDataA[4] = {1.0f, 2.0f, 3.0f, 4.0f};
    float simpleDataB[6] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
    float simpleDataC[9] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
    float simpleDataD[16] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
    
    AMathEngine::Matrix<float> A(2, 2, simpleDataA);
    A.print();
    cout << endl;

    return 0;
}