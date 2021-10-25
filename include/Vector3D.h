#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "Vector.h"

namespace A4DEngine {
    class Vector3D : public Vector {
        public:
            float x, y, z;

            // Constructor
            Vector3D();
            Vector3D(float, float, float);

            // Copy Constructor
            Vector3D(const Vector3D&);

            // Move Constructor
            Vector3D(Vector3D&&);
            
            // Destructor
            virtual ~Vector3D();

            // Scalar Multiplication
            Vector3D& operator*=(float);

            // Scalar Division
            Vector3D& operator/=(float);

            // Vector Addition
            Vector3D& operator+=(const Vector3D&);

            // Vector Subtraction
            Vector3D& operator-=(const Vector3D&);

            // returns Vector Magnitude
            float get_magnitude() const;

            // Normalize Vector
            Vector3D get_normalize_vector() const;
            Vector3D normalize_vector();

            // Print out Vector
            void show(ostream&) const;
    };

    // Scalar Multiplication
    Vector3D operator*(const Vector3D&, float);

    // Scalar Division
    Vector3D operator/(const Vector3D&, float);

    // Negate Vector
    Vector3D operator-(const Vector3D&);

    // Vector Addition
    Vector3D operator+(const Vector3D&, const Vector3D&);

    // Vector Subtraction
    Vector3D operator-(const Vector3D&, const Vector3D&);
}

#endif