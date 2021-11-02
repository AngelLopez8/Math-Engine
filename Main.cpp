#include <iostream>

#include "include/Matrix3D.h"

using std::cout;
using std::endl;

int main() {

    A4DEngine::Vector3D v1{3, 3, -1};
    A4DEngine::Vector3D v2{-2, -2, 1};
    A4DEngine::Vector3D v3{-4, -5, 2};
    
    A4DEngine::Matrix3D M{v1, v2, v3};

    cout << get_adjugate(M);  
    cout << get_inverse(M); 
    
  
    return 0;
} 