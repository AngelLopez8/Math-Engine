#ifndef MATRIX3D_HPP
#define MATRIX3D_HPP

#include "Vector3D.hpp"

class Matrix3D {
    Vector3D M[3];
public:
    // Constructors
    Matrix3D(float, float, float, float, float, float, float, float, float);
    Matrix3D(const Vector3D&, const Vector3D&, const Vector3D&);

    // Accessors
    float& operator()(int, int);
    const float& operator()(int, int) const;

    Vector3D& operator[](int);
    const Vector3D& operator[](int) const;

    // friend functions
    friend std::ostream& operator<<(std::ostream&, const Matrix3D&);    
};

// Matrix Multiplication
Matrix3D operator*(const Matrix3D&, const Matrix3D&);
Vector3D operator*(const Matrix3D&, const Vector3D&);

#endif