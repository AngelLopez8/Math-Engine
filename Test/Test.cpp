#include "../Vector/include/Vector.h"
#include "../Vector/include/Vector3D.h"
#include "../Matrix/include/Matrix.h"

void test_vector() {
    float testDataA[3] = {1.0f, 2.0f, 3.0f};
    float testDataB[4] = {1.0f, 2.0f, 3.0f, 4.0f};
}

void test_vector3D() {
    float testDataA[3] = {1.0f, 2.0f, 3.0f};
    float testDataB[3] = {1.0f, 0.0f, 3.0f};
}

void test_matrix() {
    float testDataB[4] = {1.0f, 2.0f, 3.0f, 4.0f};
    float testDataC[6] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
    float testDataD[9] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
    float testDataE[16] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};    
    float testData[9] = {1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 4.0f, 5.0f, 6.0f, 0.0f};
}