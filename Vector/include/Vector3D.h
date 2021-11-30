#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "Vector.h"

namespace AMathEngine {
    template <class T>
    class Vector3D : public Vector<T> { 
        public:
            /***************************** Constructors *****************************/
            Vector3D();     // Default Constructor 
            Vector3D(float x, float y, float z);  // Constructor passed in 3 floats
            Vector3D(const Vector3D<T>& inputVector);      // Copy Constructor
            Vector3D(Vector3D<T>&& inputVector);       // Move Constructor

            ~Vector3D();    // Destructor

            /***************************** Friend Functions *****************************/
            template <class U> friend Vector3D<U> cross(const Vector3D<U>& lhs, const Vector3D<U>& rhs);   // Cross Product
            template <class U> friend float scalar_triple_product(const Vector3D<U>&, const Vector3D<U>&, const Vector3D<U>&);   // Scalar Triple Product
    };
}

#endif