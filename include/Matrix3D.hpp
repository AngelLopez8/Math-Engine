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

float Determinant(const Matrix3D&);
Matrix3D Inverse(const Matrix3D&);

Matrix3D MakeRotationX(float);
Matrix3D MakeRotationY(float);
Matrix3D MakeRotationZ(float);
Matrix3D MakeRotation(float, const Vector3D&);
Matrix3D MakeReflection(const Vector3D&);
Matrix3D MakeInvolution(const Vector3D&);
Matrix3D MakeScale(float, float, float);
Matrix3D MakeScale(float, const Vector3D&);
Matrix3D MakeSkew(float, const Vector3D&, const Vector3D&);

#endif