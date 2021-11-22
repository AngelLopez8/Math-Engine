#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "Vector.h"

namespace AMathEngine {
    class Vector3D : public Vector { 
        public:
            Vector3D();     // Default Constructor
            Vector3D(const Vector3D&);      // Copy Constructor
            Vector3D(Vector3D&&);       // Move Constructor
            Vector3D(float, float, float);  // Constructor passed in 3 floats
            Vector3D(vector<float>);    // Constructor passed in vector
            ~Vector3D();    // Destructor
    };

    Vector3D cross(const Vector3D&, const Vector3D&);   // Cross Product
    float scalar_triple_product(const Vector3D&, const Vector3D&, const Vector3D&);   // Scalar triple product
}

#endif